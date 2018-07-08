package xyz.ruin.ElonaFoobar;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
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
    private static final String TAG = "Splash";
    private static final int INSTALL_DIALOG_ID = 0;
    private ProgressDialog installDialog;

    private String getVersionName() {
        try {
            Context context = getApplicationContext();
            PackageInfo pInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), 0);
            return pInfo.versionName;
        } catch (Exception e) {
            e.printStackTrace();
            return "error";
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.e(TAG, "onCreate()");
        super.onCreate(savedInstanceState);

        // Start the game if already installed, otherwise start installing...
        if (getVersionName().equals(PreferenceManager.getDefaultSharedPreferences(getApplicationContext()).getString("installed", ""))) {
            startGameActivity(false);
        }
        else {
            new InstallProgramTask().execute();
        }
    }

    @Override
    public Dialog onCreateDialog(int id) {
        switch (id) {
            case INSTALL_DIALOG_ID:
                installDialog = new ProgressDialog(this);
                installDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                boolean clean_install = PreferenceManager.getDefaultSharedPreferences(getApplicationContext()).getString("installed", "").isEmpty();
                installDialog.setTitle(getString(clean_install ? R.string.installing : R.string.upgrading));
                installDialog.setIndeterminate(true);
                installDialog.setCancelable(false);
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
            timer.schedule(gameStartTask, 1500);
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
        private static final int TOTAL_FILES = 1438;
        private final List<String> PRESERVE_SUBFOLDERS = Arrays.asList("asd"); // don't delete custom subfolders under these folders
        private final List<String> PRESERVE_FOLDERS = Arrays.asList("asd"); // don't delete this folder
        private final List<String> PRESERVE_FILES = Arrays.asList("asd"); // don't delete this file
        private int installedFiles = 0;
        private AlertDialog alert;

        @Override
        protected void onPreExecute() {
            showDialog(INSTALL_DIALOG_ID);
            alert = new AlertDialog.Builder(SplashScreen.this)
				.setTitle("Installation Failed")
				.setCancelable(false)
				.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
						SplashScreen.this.finish();
						return;
					}
				}).create();
        }

        @Override
        protected Boolean doInBackground(Void... params) {
            if (installDialog != null) {
                installDialog.setIndeterminate(false);
                installDialog.setMax(TOTAL_FILES);
            }
            publishProgress(installedFiles);

            AssetManager assetManager = getAssets();
            String externalFilesDir = getExternalFilesDir(null).getPath();

			try {
				// Clear out the old data if it exists (but preserve custom folders + files)
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/data"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/graphic"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/map"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/original"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/lang"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/sound"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/tmp"));
				deleteRecursive(assetManager, externalFilesDir, new File(externalFilesDir + "/user"));

				// Install the new data over the top
				copyAssetFolder(assetManager, "data", externalFilesDir + "/data");
				copyAssetFolder(assetManager, "graphic", externalFilesDir + "/graphic");
				copyAssetFolder(assetManager, "map", externalFilesDir + "/map");
				copyAssetFolder(assetManager, "original", externalFilesDir + "/original");
				copyAssetFolder(assetManager, "lang", externalFilesDir + "/lang");
				copyAssetFolder(assetManager, "runtime", externalFilesDir);
				copyAssetFolder(assetManager, "sound", externalFilesDir + "/sound");
				copyAssetFolder(assetManager, "tmp", externalFilesDir + "/tmp");
				copyAssetFolder(assetManager, "user", externalFilesDir + "/user");
            } catch(Exception e) {
				alert.setMessage(e.getMessage());
				return false;
            }

            // Remember which version the installed data is
            PreferenceManager.getDefaultSharedPreferences(getApplicationContext()).edit().putString("installed", getVersionName()).commit();

            publishProgress(++installedFiles);
            Log.d(TAG, "Total number of files copied: " + installedFiles);
            return true;
        }

        void deleteRecursive(AssetManager assetManager, String externalFilesDir, File fileOrDirectory) {
            String parentFolder = fileOrDirectory.getParentFile().getName().toLowerCase();
            String fileOrDirectoryName = fileOrDirectory.getName().toLowerCase();
            if (fileOrDirectory.isDirectory()) {
                // Don't delete the folder if it is in the preserve folders list
                if (PRESERVE_FOLDERS.contains(fileOrDirectoryName))
                    return;

                // Don't delete the folder if its parent is in the preserve subfolders list, and it doesn't exist in the APK assets (so must be custom data)
                if (PRESERVE_SUBFOLDERS.contains(parentFolder) && !assetExists(assetManager, fileOrDirectory.getPath().substring(externalFilesDir.length()+1)))
                    return;

                for (File child : fileOrDirectory.listFiles())
                    deleteRecursive(assetManager, externalFilesDir, child);
            }
            else {
                // Don't delete the file if it's in the preserve files list
                if (PRESERVE_FILES.contains(fileOrDirectoryName))
                    return;
            }

            fileOrDirectory.delete();
        }

        // Returns true if an asset exists in the APK (either a directory or a file)
        // eg. assetExists("data/sound") or assetExists("data/font", "unifont.ttf") would both return true
        private boolean assetExists(AssetManager assetManager, String assetPath) {
		    return assetExists(assetManager, assetPath, "");
        }

        private boolean assetExists(AssetManager assetManager, String assetPath, String assetName) {
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

        // Pinched from http://stackoverflow.com/questions/16983989/copy-directory-from-assets-to-data-folder
        private boolean copyAssetFolder(AssetManager assetManager, String fromAssetPath, String toPath) throws Exception {
            try {
                String[] files = assetManager.list(fromAssetPath);
                new File(toPath).mkdirs();
                boolean res = true;
                for (String file : files)
                {
                    if (file.contains("."))
                        res &= copyAsset(assetManager, fromAssetPath + "/" + file, toPath + "/" + file);
                    else
                        res &= copyAssetFolder(assetManager, fromAssetPath + "/" + file, toPath + "/" + file);
                }
                return res;
            } catch (Exception e) {
                e.printStackTrace();
                throw e;
            }
        }

        private boolean copyAsset(AssetManager assetManager, String fromAssetPath, String toPath) throws Exception {
            publishProgress(++installedFiles, TOTAL_FILES);
            InputStream in = null;
            OutputStream out = null;
            try {
              in = assetManager.open(fromAssetPath);
              new File(toPath).createNewFile();
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

        private void copyFile(InputStream in, OutputStream out) throws IOException {
            byte[] buffer = new byte[1024];
            int read;
            while((read = in.read(buffer)) != -1) {
              out.write(buffer, 0, read);
            }
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
