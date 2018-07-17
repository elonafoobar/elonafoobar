package xyz.ki.elonafoobar;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.util.Log;

public class ExtractZipTask extends AsyncTask<Void, Integer, Long> {
    private static final String TAG = ExtractZipTask.class.getName();
    private File inputFile;
    private File outputDir;
    private String innerDir;
    private Context context;
    private ProgressDialog dialog;
    private Throwable exception;

    public ExtractZipTask(File inputFile, File outputDir,
                          String innerDir, Context context) {
        this.inputFile = inputFile;
        this.outputDir = outputDir;
        this.innerDir = innerDir;

        if (context != null) {
            dialog = new ProgressDialog(context);
        } else {
            dialog = null;
        }

        this.context = context;
    }

    @Override
    protected void onPreExecute() {
        if (dialog != null) {
            dialog.setTitle(R.string.extracting);
            dialog.setMessage(inputFile.getName());
            dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
            dialog.setCancelable(false);
            dialog.show();
        }
    }

    @Override
    protected Long doInBackground(Void... params) {
        try {
            return unzip();
        } catch (Exception e) {
            if (inputFile.exists()) {
                inputFile.delete();
            }
            exception = e;
            return null;
        }
    }

    @Override
    protected void onProgressUpdate(Integer... progress) {
        if (dialog == null) {
            return;
        }
        if (progress.length > 1) {
            int max = progress[1];
            dialog.setMax(max);
        } else {
            dialog.setProgress(progress[0].intValue());
        }
    }

    @Override
    protected void onPostExecute(Long result) {
        if (dialog != null && dialog.isShowing()) {
            dialog.dismiss();
        }

        if (exception != null) {
            Log.e(TAG, "Extraction failed", exception);

            if (context != null) {
                AlertDialog alert = new AlertDialog.Builder(context)
                    .setTitle(R.string.installationFailed)
                    .setMessage(context.getString(R.string.extractionFailed, inputFile.toString(), exception.toString()))
                    .setCancelable(false)
                    .setPositiveButton(R.string.ok, new DialogOnClickListenerWithContext(context)).create();
                alert.show();
            }
        }
    }


    private long unzip() throws Exception {
        long extractedSize = 0l;
        Enumeration<? extends ZipEntry> entries;
        ZipFile zip = new ZipFile(inputFile);
        long uncompressedSize = getUncompressedSize(zip);

        publishProgress(0, (int)uncompressedSize);
        Log.d(TAG, "Extracting from " + inputFile + " to " + outputDir);

        entries = zip.entries();

        try {
            while (entries.hasMoreElements()) {
                ZipEntry entry = entries.nextElement();
                if (entry.isDirectory()) {
                    continue;
                }
                String filename = entry.getName().replaceFirst("^" + innerDir + "/", "");
                File destination = new File(outputDir, filename);
                if (!destination.getParentFile().exists()) {
                    destination.getParentFile().mkdirs();
                }
                FileOutputStream outStream = new FileOutputStream(destination);
                extractedSize += AssetUtils.copy(zip.getInputStream(entry), outStream);
                publishProgress((int)extractedSize);
                outStream.close();
            }
        } finally {
            try {
                zip.close();
            } catch (Exception e) {
            }
        }
        Log.d(TAG, "Extracted " + extractedSize + " bytes");
        return extractedSize;
    }

    private long getUncompressedSize(ZipFile file) {
        Enumeration<? extends ZipEntry> entries = file.entries();
        long originalSize = 0l;
        while (entries.hasMoreElements()) {
            ZipEntry entry = entries.nextElement();
            if (entry.getSize() >= 0) {
                originalSize += entry.getSize();
            }
        }
        return originalSize;
    }

    private class DialogOnClickListenerWithContext implements DialogInterface.OnClickListener {
        private Context context;

        public DialogOnClickListenerWithContext(Context context) {
            this.context = context;
        }

        @Override
        public void onClick(DialogInterface dialog, int id) {
            if (this.context instanceof Activity) {
                ((Activity)this.context).finish();
            }
        }
    }
}
