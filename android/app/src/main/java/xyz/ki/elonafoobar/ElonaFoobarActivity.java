package xyz.ki.elonafoobar;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.Log;
import android.view.View;
import android.widget.Toast;
import org.libsdl.app.SDLActivity;

public class ElonaFoobarActivity extends SDLActivity
{
    private static final String TAG = "Elona foobar";

    // *ドクン ドクン*
    private static final long[] VIBRATION_TIMINGS    = {100, 100, 150, 150, 350, 100, 150, 150};
    private static final int[]  VIBRATION_AMPLITUDES = {0,   80,  0,   140, 0,   80,  0,   140};

    private boolean navBarEnabled = true;

    @Override
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "SDL2_image",
            "SDL2_mixer",
            "SDL2_ttf",
            "lua",
            "boost_filesystem",
            "boost_system",
            "boost_iostreams",
            "snail",
            "Elona_foobar"
        };
    }

    public void setNavigationBarVisibility(final boolean enable) {
        navBarEnabled = enable;

        if (!navBarEnabled)
        {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    hideSystemUI();
                    getWindow().getDecorView().setOnSystemUiVisibilityChangeListener
                        (new View.OnSystemUiVisibilityChangeListener() {
                            @Override
                            public void onSystemUiVisibilityChange(int visibility) {
                                hideSystemUI();
                            }
                        });
                }
            });
        }
    }

    public void toast(final String message, final int length) {
        try {
            runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(getApplicationContext(), message, length).show();
                }
            });
        } catch(Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }

    public void vibrate(int duration) {
        try {
            Vibrator vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.cancel();

            Log.d(TAG, "VIbrate " + duration);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                VibrationEffect vibeEffect =
                    VibrationEffect.createOneShot((int)duration,
                                                  VibrationEffect.DEFAULT_AMPLITUDE);
                vibrator.vibrate(vibeEffect);
                Log.d(TAG, "VIbrate new");
            } else {
                vibrator.vibrate((int)duration);
                Log.d(TAG, "VIbrate old");
            }
        } catch(Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }

    public void vibratePulse() {
        try {
            Vibrator vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.cancel();

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                VibrationEffect vibeEffect =
                    VibrationEffect.createWaveform(VIBRATION_TIMINGS,
                                                   VIBRATION_AMPLITUDES,
                                                   -1);
                vibrator.vibrate(vibeEffect);
            } else {
                vibrator.vibrate(VIBRATION_TIMINGS, -1);
            }
        } catch(Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }


    // The setup below is for preventing the soft keyboard from
    // disabling immersive mode.
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        if (!navBarEnabled)
        {
            hideSystemUI();
        }
    }
    private void hideSystemUI() {
            final View decorView = getWindow().getDecorView();
            decorView.setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }
    private final Handler mHideHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            hideSystemUI();
        }
    };
    private void delayedHide(int delayMillis) {
        mHideHandler.removeMessages(0);
        mHideHandler.sendEmptyMessageDelayed(0, delayMillis);
    }

}
