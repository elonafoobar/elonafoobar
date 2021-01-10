# Note about dependencies

This crate implicitly depends on these things:

- `elonafoobar_log` crate
  - `elonafoobar_log::trace`

In addition, this crate assumes that each module which uses `#[lua_function]` attribute defines `MODULE_PATH` of `&'static str` constant.
