package xyz.ruin.elonafoobar;

import org.libsdl.app.SDLActivity;

public class ElonaFoobarActivity extends SDLActivity
{
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
}
