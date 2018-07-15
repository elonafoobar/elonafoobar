package xyz.ki.elonafoobar;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.Log;
import android.view.View;
import org.libsdl.app.SDLActivity;

public class ElonaFoobarActivity extends SDLActivity
{
    private static final String TAG = "ElonaFoobar";
    private static final long[] VIBRATION_TIMINGS    = {100, 100, 150, 150, 350};
    private static final int[]  VIBRATION_AMPLITUDES = {0,   50, 0,   100, 0};

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
            "ElonaFoobar"
        };
    }

    public void setNavigationBarVisibility(final boolean enable)
    {
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


    public void vibrate(long duration) {
        try {
            Vibrator vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.cancel();

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                VibrationEffect vibeEffect =
                    VibrationEffect.createOneShot(duration,
                                                  VibrationEffect.DEFAULT_AMPLITUDE);
                vibrator.vibrate(vibeEffect);
            } else {
                vibrator.vibrate(duration);
            }
        } catch(Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }

    public void vibratePulse(int repeat) {
        try {
            Vibrator vibrator = (Vibrator)getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.cancel();

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                VibrationEffect vibeEffect =
                    VibrationEffect.createWaveform(VIBRATION_TIMINGS,
                                                   VIBRATION_AMPLITUDES,
                                                   repeat);
                vibrator.vibrate(vibeEffect);
            } else {
                vibrator.vibrate(VIBRATION_TIMINGS, repeat);
            }
        } catch(Exception e) {
            Log.e(TAG, e.getMessage());
        }
    }
}
