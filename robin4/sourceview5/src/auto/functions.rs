// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use glib::translate::*;
#[cfg(any(feature = "v5_2", feature = "dox"))]
#[cfg_attr(feature = "dox", doc(cfg(feature = "v5_2")))]
use std::boxed::Box as Box_;

#[doc(alias = "gtk_source_check_version")]
pub fn check_version(major: u32, minor: u32, micro: u32) -> bool {
    assert_initialized_main_thread!();
    unsafe { from_glib(ffi::gtk_source_check_version(major, minor, micro)) }
}

#[doc(alias = "gtk_source_finalize")]
pub fn finalize() {
    assert_initialized_main_thread!();
    unsafe {
        ffi::gtk_source_finalize();
    }
}

#[doc(alias = "gtk_source_get_major_version")]
#[doc(alias = "get_major_version")]
pub fn major_version() -> u32 {
    assert_initialized_main_thread!();
    unsafe { ffi::gtk_source_get_major_version() }
}

#[doc(alias = "gtk_source_get_micro_version")]
#[doc(alias = "get_micro_version")]
pub fn micro_version() -> u32 {
    assert_initialized_main_thread!();
    unsafe { ffi::gtk_source_get_micro_version() }
}

#[doc(alias = "gtk_source_get_minor_version")]
#[doc(alias = "get_minor_version")]
pub fn minor_version() -> u32 {
    assert_initialized_main_thread!();
    unsafe { ffi::gtk_source_get_minor_version() }
}

#[doc(alias = "gtk_source_init")]
pub fn init() {
    assert_initialized_main_thread!();
    unsafe {
        ffi::gtk_source_init();
    }
}

#[cfg(any(feature = "v5_2", feature = "dox"))]
#[cfg_attr(feature = "dox", doc(cfg(feature = "v5_2")))]
#[doc(alias = "gtk_source_scheduler_add")]
pub fn scheduler_add<P: FnOnce(i64) -> bool + Send + Sync + 'static>(callback: P) -> usize {
    assert_initialized_main_thread!();
    let callback_data: Box_<P> = Box_::new(callback);
    unsafe extern "C" fn callback_func<P: FnOnce(i64) -> bool + Send + Sync + 'static>(
        deadline: i64,
        user_data: glib::ffi::gpointer,
    ) -> glib::ffi::gboolean {
        let callback: Box_<P> = Box_::from_raw(user_data as *mut _);
        (*callback)(deadline).into_glib()
    }
    let callback = Some(callback_func::<P> as _);
    let super_callback0: Box_<P> = callback_data;
    unsafe { ffi::gtk_source_scheduler_add(callback, Box_::into_raw(super_callback0) as *mut _) }
}

#[cfg(any(feature = "v5_2", feature = "dox"))]
#[cfg_attr(feature = "dox", doc(cfg(feature = "v5_2")))]
#[doc(alias = "gtk_source_scheduler_add_full")]
pub fn scheduler_add_full<P: Fn(i64) -> bool + Send + Sync + 'static>(callback: P) -> usize {
    assert_initialized_main_thread!();
    let callback_data: Box_<P> = Box_::new(callback);
    unsafe extern "C" fn callback_func<P: Fn(i64) -> bool + Send + Sync + 'static>(
        deadline: i64,
        user_data: glib::ffi::gpointer,
    ) -> glib::ffi::gboolean {
        let callback: &P = &*(user_data as *mut _);
        (*callback)(deadline).into_glib()
    }
    let callback = Some(callback_func::<P> as _);
    unsafe extern "C" fn notify_func<P: Fn(i64) -> bool + Send + Sync + 'static>(
        data: glib::ffi::gpointer,
    ) {
        let _callback: Box_<P> = Box_::from_raw(data as *mut _);
    }
    let destroy_call2 = Some(notify_func::<P> as _);
    let super_callback0: Box_<P> = callback_data;
    unsafe {
        ffi::gtk_source_scheduler_add_full(
            callback,
            Box_::into_raw(super_callback0) as *mut _,
            destroy_call2,
        )
    }
}

#[cfg(any(feature = "v5_2", feature = "dox"))]
#[cfg_attr(feature = "dox", doc(cfg(feature = "v5_2")))]
#[doc(alias = "gtk_source_scheduler_remove")]
pub fn scheduler_remove(handler_id: usize) {
    assert_initialized_main_thread!();
    unsafe {
        ffi::gtk_source_scheduler_remove(handler_id);
    }
}

#[doc(alias = "gtk_source_utils_escape_search_text")]
pub fn utils_escape_search_text(text: &str) -> glib::GString {
    assert_initialized_main_thread!();
    unsafe {
        from_glib_full(ffi::gtk_source_utils_escape_search_text(
            text.to_glib_none().0,
        ))
    }
}

#[doc(alias = "gtk_source_utils_unescape_search_text")]
pub fn utils_unescape_search_text(text: &str) -> glib::GString {
    assert_initialized_main_thread!();
    unsafe {
        from_glib_full(ffi::gtk_source_utils_unescape_search_text(
            text.to_glib_none().0,
        ))
    }
}
