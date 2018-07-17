package xyz.ki.elonafoobar;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import android.net.Uri;
import android.content.Context;
import android.content.ContentResolver;
import android.content.res.AssetManager;
import android.util.Log;

public class AssetUtils {
    private static final String TAG = AssetUtils.class.getName();
    private static final int BUFFER_SIZE = 1024;

    // Returns true if an asset exists in the APK (either a directory
    // or a file) eg. assetExists("data/sound") or
    // assetExists("data/font", "unifont.ttf") would both return true
    public static boolean assetExists(AssetManager assetManager, String assetPath) {
        return assetExists(assetManager, assetPath, "");
    }

    public static boolean assetExists(AssetManager assetManager, String assetPath, String assetName) {
        try {
            String[] files = assetManager.list(assetPath);
            if (assetName.isEmpty())
                return files.length > 0; // folder exists
            for (String file : files) {
                if (file.equalsIgnoreCase(assetName))
                    return true; // file exists
            }
            return false;
        } catch (Exception e) {
            Log.e(TAG, e.getMessage(), e);
            e.printStackTrace();
            return false;
        }
    }

    public static void deleteRecursive(AssetManager assetManager,
                                       File fileOrDirectory) {
        String parentFolder = fileOrDirectory.getParentFile().getName().toLowerCase();
        String fileOrDirectoryName = fileOrDirectory.getName().toLowerCase();

        if (fileOrDirectory.isDirectory()) {
            for (File child : fileOrDirectory.listFiles())
                deleteRecursive(assetManager, child);
        }

        fileOrDirectory.delete();
    }

    public static boolean copyAsset(AssetManager assetManager,
                                    String fromAssetPath,
                                    File toPath) throws Exception {
        try (InputStream in = assetManager.open(fromAssetPath)) {
            copyStreamTo(in, toPath);
        }
        return true;
    }

    public static void copyUriData(Uri uri, File toPath, Context context) throws Exception {
        ContentResolver resolver = context.getContentResolver();
        try (InputStream in = resolver.openInputStream(uri)) {
            copyStreamTo(in, toPath);
        }
    }

    private static void copyStreamTo(InputStream in, File toPath) throws Exception {
        toPath.createNewFile();
        OutputStream out = new FileOutputStream(toPath);
        copy(in, out);
        out.flush();
        out.close();
        out = null;
    }

    public static int copy(InputStream input, OutputStream output) throws Exception, IOException {
        byte[] buffer = new byte[BUFFER_SIZE];

        BufferedInputStream in = new BufferedInputStream(input, BUFFER_SIZE);
        BufferedOutputStream out = new BufferedOutputStream(output, BUFFER_SIZE);
        int count = 0, n = 0;
        try {
            while ((n = in.read(buffer, 0, BUFFER_SIZE)) != -1) {
                out.write(buffer, 0, n);
                count += n;
            }
            out.flush();
        } finally {
            try {
                out.close();
            } catch (IOException e) {
                Log.e(TAG, e.getMessage(), e);
            }
            try {
                in.close();
            } catch (IOException e) {
                Log.e(TAG, e.getMessage(), e);
            }
        }
        return count;
    }

    public static int countFiles(AssetManager assetManager,
                                 List<String> paths) throws Exception
    {
        int ret = 0;

        for (String path : paths) {
            String[] files = assetManager.list(path);
            ret += files.length;

            List<String> children = new ArrayList<String>();

            for (int i = 0; i < files.length; i++) {
                if (!files[i].contains(".")) {
                    children.add(path + "/" + files[i]);
                }
            }

            ret += countFiles(assetManager, children);
        }

        return ret;
    }
}
