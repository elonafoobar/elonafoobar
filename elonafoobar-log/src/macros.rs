// It is public only for macro expansions.
pub mod __impl {
    pub use log::{debug, error, info, trace, warn};
}

#[macro_export]
macro_rules! error {
    ($( $arg:tt )+) => (
        $crate::macros::__impl::error!(target: "_native_", $( $arg )+);
    )
}

#[macro_export]
macro_rules! warn {
    ($( $arg:tt )+) => (
        $crate::macros::__impl::warn!(target: "_native_", $( $arg )+);
    )
}

#[macro_export]
macro_rules! info {
    ($( $arg:tt )+) => (
        $crate::macros::__impl::info!(target: "_native_", $( $arg )+);
    )
}

#[macro_export]
macro_rules! debug {
    ($( $arg:tt )+) => (
        $crate::macros::__impl::debug!(target: "_native_", $( $arg )+);
    )
}

#[macro_export]
macro_rules! trace {
    ($( $arg:tt )+) => (
        $crate::macros::__impl::trace!(target: "_native_", $( $arg )+);
    )
}
