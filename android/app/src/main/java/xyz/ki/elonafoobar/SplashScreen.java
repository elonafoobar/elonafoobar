package xyz.ki.elonafoobar;

import java.io.File;
import java.net.URI;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Application;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.*;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.*;
import android.widget.ImageView;
import android.widget.Toast;

public class SplashScreen extends Activity {
    private static final String TAG = SplashScreen.class.getName();
    private static final String INSTALLED = "installed";
    private static final String MIME_TYPE_ZIP = "application/zip";
    private static final String ZIP_FILESYSTEM_PROTOCOL = "jar";
    private static final String ELONA_FOLDER_NAME = "elona";
    private static final String ELONA_ZIP_FOLDER_NAME = "elona122.zip";
    private static final String ELONA_ASSET_FILENAME = "original";
    private static final int INSTALL_DIALOG_ID = 0;
    private static final int FILE_SELECT_CODE = 42;
    private static final int SCREEN_WAIT_MS = 1500;

    private boolean afterActivity = false;
    private Uri zipUri;

    private String getVersionName() {
        try {
            Context context = getApplicationContext();
            PackageInfo pInfo = context.getPackageManager()
                .getPackageInfo(context.getPackageName(), 0);
            return pInfo.versionName;
        } catch (Exception e) {
            Log.e(TAG, e.toString(), e);
            e.printStackTrace();
            return "error";
        }
    }

    private boolean isGameInstalled() {
        Context context = getApplicationContext();
        String installed = PreferenceManager
            .getDefaultSharedPreferences(context).getString(INSTALLED, "");
        return getVersionName().equals(installed);
    }

    private void setInstalledVersion(String name) {
        Context context = getApplicationContext();
        PreferenceManager.getDefaultSharedPreferences(context)
            .edit()
            .putString(INSTALLED, name)
            .commit();
    }

    private void fail(String message)
    {
        AlertDialog failAlert = new AlertDialog.Builder(SplashScreen.this)
            .setTitle(R.string.installationFailed)
            .setMessage(message)
            .setCancelable(false)
            .setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        SplashScreen.this.finish();
                        return;
                    }
                }).create();
        failAlert.show();
    }

    private void promptForOriginalAssetArchive()
    {
        AlertDialog alert = new AlertDialog.Builder(SplashScreen.this)
            .setMessage(R.string.chooseArchiveFile)
            .setCancelable(false)
            .setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        promptForZipFile();
                    }
                }).create();
        alert.show();
    }

    private void promptForZipFile()
    {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType(MIME_TYPE_ZIP);
        intent.addCategory(Intent.CATEGORY_OPENABLE);

        try {
            startActivityForResult(Intent.createChooser(intent,
                                                        getString(R.string.chooseArchiveFile)),
                                   FILE_SELECT_CODE);
        } catch (android.content.ActivityNotFoundException ex) {
            // No file manager was installed.
            Toast.makeText(this, R.string.installFileManager, Toast.LENGTH_SHORT).show();
            fail(getString(R.string.archiveNotFound));
        }
    }

    private boolean verifyArchiveFile(File file) throws Exception
    {
        Path path = file.toPath();
        ZipInputStream zip = new ZipInputStream(Files.newInputStream(
                path, StandardOpenOption.READ));
        ZipEntry entry = null;

        while((entry = zip.getNextEntry()) != null) {
            if (entry.getName().startsWith(ELONA_FOLDER_NAME)) {
                return true;
            }
        }

        return false;
    }

    private String extractArchiveFile(Uri uri)
    {
        File externalFilesDir = getExternalFilesDir(null);
        File zipFile = new File(externalFilesDir, ELONA_ZIP_FOLDER_NAME);

        try
        {
            AssetUtils.copyUriData(uri, zipFile, SplashScreen.this);
            if (verifyArchiveFile(zipFile)) {
                new ExtractZipTask(zipFile,
                                   externalFilesDir,
                                   ELONA_FOLDER_NAME,
                                   SplashScreen.this)
                    .execute();
            } else {
                return getString(R.string.dirNotFound, ELONA_FOLDER_NAME, zipFile.toString());
            }
        }
        catch (Exception e)
        {
            Log.e(TAG, e.toString(), e);
            return e.toString();
        }

        return null;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        afterActivity = true;
        if (resultCode != RESULT_OK) {
            return;
        }

        if (requestCode == FILE_SELECT_CODE)
        {
            zipUri = data.getData();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (afterActivity) {
            if (zipUri == null) {
                fail(getString(R.string.archiveNotFound));
            } else {
                String errorMessage = extractArchiveFile(zipUri);
                if (errorMessage != null) {
                    fail(errorMessage);
                } else {
                    // BUG: Installer's dialog will be overlapped while
                    // zip extraction task's dialog is still up. For now,
                    // specify whether or not to display the installer's
                    // dialog in InstallProgramTask.
                    new InstallProgramTask(isGameInstalled(), false, SplashScreen.this)
                        .execute();
                }
            }
        }
    }

    private boolean areOriginalAssetsBundled() {
        return AssetUtils.assetExists(getAssets(), ELONA_ASSET_FILENAME);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate()");
        super.onCreate(savedInstanceState);

        if (isGameInstalled()) {
            startGameActivity(false);
        }
        else {
            boolean assetsBundled = areOriginalAssetsBundled();
            if (assetsBundled) {
                new InstallProgramTask(isGameInstalled(), true, getApplicationContext())
                    .execute();
            } else {
                promptForOriginalAssetArchive();
            }
        }
    }

    private void startGameActivity(boolean delay) {
        if (!delay) {
            runOnUiThread(new StartGameRunnable());
        }
        else {
            // Wait 1.5 seconds, then start game
            Timer timer = new Timer();
            TimerTask gameStartTask = new TimerTask() {
                    @Override
                    public void run() {
                        runOnUiThread(new StartGameRunnable());
                    }
                };
            timer.schedule(gameStartTask, SCREEN_WAIT_MS);
        }
    }

    private final class StartGameRunnable implements Runnable {
        @Override
        public void run() {
            Intent intent = new Intent(SplashScreen.this, ElonaFoobarActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
            startActivity(intent);
            finish();
            overridePendingTransition(0, 0);
        }
    }

    private class InstallProgramTask extends AsyncTask<Void, Integer, Boolean> {
        private final List<FolderInfo> folders = Arrays.asList(
            new FolderInfo[] {
                new FolderInfo("data"),
                new FolderInfo("graphic"),
                new FolderInfo("map"),
                new FolderInfo("original"),
                new FolderInfo("lang"),
                new FolderInfo("runtime", ".", false),
                new FolderInfo("sound"),
                new FolderInfo("tmp"),
                new FolderInfo("user", true)
            }
        );

        private boolean alreadyInstalled;
        private boolean showDialog;
        private int totalFiles = 0;
        private int installedFiles = 0;
        private Context context;
        private ProgressDialog installDialog;
        private AlertDialog alert;


        private class FolderInfo {
            public FolderInfo(String path) {
                this(path, false);
            }
            public FolderInfo(String path, boolean preserve) {
                this(path, path, preserve);
            }
            public FolderInfo(String sourcePath, String destPath, boolean preserve) {
                this.sourcePath = sourcePath;
                this.destPath = destPath;
                this.preserve = preserve;
            }

            public String sourcePath;
            public String destPath;
            public boolean preserve;
        }


        public InstallProgramTask(boolean alreadyInstalled, boolean showDialog, Context context) {
            this.alreadyInstalled = alreadyInstalled;

            if (context != null) {
                installDialog = new ProgressDialog(context);
            } else {
                installDialog = null;
            }

            this.context = context;
        }

        @Override
        protected void onPreExecute() {
            if (installDialog != null && showDialog) {
                installDialog = new ProgressDialog(context);
                installDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                installDialog.setTitle(getString(alreadyInstalled ? R.string.upgrading : R.string.installing));
                installDialog.setIndeterminate(true);
                installDialog.setCancelable(false);
                installDialog.show();
            }

            alert = new AlertDialog.Builder(SplashScreen.this)
                .setTitle(R.string.installationFailed)
                .setCancelable(false)
                .setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            SplashScreen.this.finish();
                            return;
                        }
                    }).create();
        }

        private List<String> getAssetFolders(String externalFilesDir) {
            List<String> result = new ArrayList<String>();
            for (FolderInfo folder : folders) {
                result.add(folder.sourcePath);
            }
            return result;
        }

        private void clearExistingData(AssetManager assetManager,
                                       String externalFilesDir) throws Exception
        {
            // Clear out the old data if it exists (but preserve
            // custom folders + files)
            for (FolderInfo folder : folders) {
                if (!folder.preserve) {
                    AssetUtils.deleteRecursive(assetManager,
                                               new File(externalFilesDir, folder.destPath));
                }
            }
        }

        private void copyNewData(AssetManager assetManager,
                                 String externalFilesDir) throws Exception
        {
            // Install the new data over the top
            for (FolderInfo folder : folders) {
                copyAssetFolder(assetManager,
                                folder.sourcePath,
                                new File(externalFilesDir, folder.destPath));
            }
        }

        @Override
        protected Boolean doInBackground(Void... params) {

            AssetManager assetManager = getAssets();
            String externalFilesDir = getExternalFilesDir(null).getPath();

            try {
                totalFiles = AssetUtils.countFiles(assetManager,
                                                   getAssetFolders(externalFilesDir));
            } catch(Exception e) {
                Log.e(TAG, e.toString(), e);
                alert.setMessage(getString(R.string.errorTallyingFiles, e.toString()));
                return false;
            }

            if (installDialog != null) {
                installDialog.setIndeterminate(false);
                installDialog.setMax(totalFiles);
            }

            publishProgress(installedFiles);

            try {
                // TODO: This would clear copied assets from elona122.zip.
                //clearExistingData(assetManager, externalFilesDir);
                copyNewData(assetManager, externalFilesDir);
            } catch(Exception e) {
                Log.e(TAG, e.toString(), e);
                alert.setMessage(getString(R.string.errorCopyingFiles, externalFilesDir, e.toString()));
                return false;
            }

            // Remember which version the installed data is
            setInstalledVersion(getVersionName());

            publishProgress(++installedFiles);
            Log.d(TAG, "Total number of files copied: " + installedFiles);
            return true;
        }

        // Pinched from http://stackoverflow.com/questions/16983989/copy-directory-from-assets-to-data-folder
        private boolean copyAssetFolder(AssetManager assetManager,
                                        String fromAssetPath,
                                        File toPath) throws Exception {
            try {
                String[] files = assetManager.list(fromAssetPath.toString());
                toPath.mkdirs();
                boolean success = true;
                for (String filename : files) {
                    String sourceFilePath = fromAssetPath + "/" + filename;
                    File destFile = new File(toPath, filename);

                    if (filename.contains(".")) {
                        success &= copyAsset(assetManager, sourceFilePath, destFile);
                    } else {
                        success &= copyAssetFolder(assetManager, sourceFilePath, destFile);
                    }
                }
                return success;
            } catch (Exception e) {
                Log.e(TAG, e.toString(), e);
                e.printStackTrace();
                throw e;
            }
        }

        private boolean copyAsset(AssetManager assetManager,
                                  String fromAssetPath,
                                  File toPath) throws Exception {
            publishProgress(++installedFiles, totalFiles);
            return AssetUtils.copyAsset(assetManager, fromAssetPath, toPath);
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            if (installDialog == null) {
                return;
            }
            installDialog.setProgress(values[0]);
        }

        @Override
        protected void onPostExecute(Boolean result) {
            if (installDialog != null && installDialog.isShowing()) {
                installDialog.dismiss();
            }

            if(result) {
                startGameActivity(true);
            } else {
                alert.show();
            }
        }
    }
}
