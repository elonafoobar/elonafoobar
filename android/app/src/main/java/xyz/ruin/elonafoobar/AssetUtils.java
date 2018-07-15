package xyz.ki.elonafoobar;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;

import android.content.res.AssetManager;

public class AssetUtils {
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
        InputStream in = null;
        OutputStream out = null;
        try {
            in = assetManager.open(fromAssetPath);
            toPath.createNewFile();
            out = new FileOutputStream(toPath);
            copyFile(in, out);
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
            return true;
        } catch(Exception e) {
            e.printStackTrace();
            throw e;
        }
    }

    public static void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while((read = in.read(buffer)) != -1) {
            out.write(buffer, 0, read);
        }
    }


    public static int tallyFiles(AssetManager assetManager,
                                 List<String> paths) throws Exception
    {
        int ret = 0;

        for (String path : paths) {
            ret += tallyFiles(assetManager, path);
        }

        return ret;
    }

    private static int tallyFiles(AssetManager assetManager, String path) throws Exception
    {
        return assetManager.list(path).length;
    }
}
