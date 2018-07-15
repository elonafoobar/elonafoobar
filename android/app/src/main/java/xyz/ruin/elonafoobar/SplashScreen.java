package xyz.ki.elonafoobar;

import java.io.File;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.Application;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.app.AlertDialog;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.content.DialogInterface;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.*;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.*;
import android.widget.ImageView;

public class SplashScreen extends Activity {
    private static final String TAG = "SplashScreen";
    private static final String INSTALLED = "installed";
    private static final int INSTALL_DIALOG_ID = 0;
    private static final int SCREEN_WAIT_MS = 1500;

    private ProgressDialog installDialog;

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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate()");
        super.onCreate(savedInstanceState);

        if (isGameInstalled()) {
            startGameActivity(false);
        }
        else {
            new InstallProgramTask().execute();
        }
    }

    private ProgressDialog createInstallDialog()
    {
        ProgressDialog dialog = new ProgressDialog(this);
        dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        boolean alreadyInstalled = isGameInstalled();
        dialog.setTitle(getString(alreadyInstalled ? R.string.upgrading : R.string.installing));
        dialog.setIndeterminate(true);
        dialog.setCancelable(false);
        return dialog;
    }

    @Override
    public Dialog onCreateDialog(int id) {
        switch (id) {
        case INSTALL_DIALOG_ID:
            ProgressDialog dialog = createInstallDialog();
            installDialog = dialog;
            return installDialog;
        default:
            return null;
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

        private int totalFiles = 0;
        private int installedFiles = 0;
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


        @Override
        protected void onPreExecute() {
            showDialog(INSTALL_DIALOG_ID);
            alert = new AlertDialog.Builder(SplashScreen.this)
                .setTitle(R.string.installation_failed)
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
                result.add(new File(externalFilesDir, folder.sourcePath).toString());
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
                totalFiles = AssetUtils.tallyFiles(assetManager,
                                                   getAssetFolders(externalFilesDir));
            } catch(Exception e) {
                Log.e(TAG, e.toString(), e);
                alert.setMessage(e.toString());
                return false;
            }

            if (installDialog != null) {
                installDialog.setIndeterminate(false);
                installDialog.setMax(totalFiles);
            }
            publishProgress(installedFiles);

            try {
                clearExistingData(assetManager, externalFilesDir);
                copyNewData(assetManager, externalFilesDir);
            } catch(Exception e) {
                Log.e(TAG, e.toString(), e);
                alert.setMessage(e.toString());
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
            removeDialog(INSTALL_DIALOG_ID);
            if(result) {
                startGameActivity(true);
            } else {
                alert.show();
            }
        }
    }
}
