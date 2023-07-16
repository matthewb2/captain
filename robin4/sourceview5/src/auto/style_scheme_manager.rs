// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::StyleScheme;
use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceStyleSchemeManager")]
    pub struct StyleSchemeManager(Object<ffi::GtkSourceStyleSchemeManager, ffi::GtkSourceStyleSchemeManagerClass>);

    match fn {
        type_ => || ffi::gtk_source_style_scheme_manager_get_type(),
    }
}

impl StyleSchemeManager {
    #[doc(alias = "gtk_source_style_scheme_manager_new")]
    pub fn new() -> StyleSchemeManager {
        assert_initialized_main_thread!();
        unsafe { from_glib_full(ffi::gtk_source_style_scheme_manager_new()) }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`StyleSchemeManager`] objects.
    ///
    /// This method returns an instance of [`StyleSchemeManagerBuilder`](crate::builders::StyleSchemeManagerBuilder) which can be used to create [`StyleSchemeManager`] objects.
    pub fn builder() -> StyleSchemeManagerBuilder {
        StyleSchemeManagerBuilder::new()
    }

    #[doc(alias = "gtk_source_style_scheme_manager_append_search_path")]
    pub fn append_search_path(&self, path: &str) {
        unsafe {
            ffi::gtk_source_style_scheme_manager_append_search_path(
                self.to_glib_none().0,
                path.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_force_rescan")]
    pub fn force_rescan(&self) {
        unsafe {
            ffi::gtk_source_style_scheme_manager_force_rescan(self.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_get_scheme")]
    #[doc(alias = "get_scheme")]
    pub fn scheme(&self, scheme_id: &str) -> Option<StyleScheme> {
        unsafe {
            from_glib_none(ffi::gtk_source_style_scheme_manager_get_scheme(
                self.to_glib_none().0,
                scheme_id.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_get_scheme_ids")]
    #[doc(alias = "get_scheme_ids")]
    pub fn scheme_ids(&self) -> Vec<glib::GString> {
        unsafe {
            FromGlibPtrContainer::from_glib_none(
                ffi::gtk_source_style_scheme_manager_get_scheme_ids(self.to_glib_none().0),
            )
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_get_search_path")]
    #[doc(alias = "get_search_path")]
    pub fn search_path(&self) -> Vec<glib::GString> {
        unsafe {
            FromGlibPtrContainer::from_glib_none(
                ffi::gtk_source_style_scheme_manager_get_search_path(self.to_glib_none().0),
            )
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_prepend_search_path")]
    pub fn prepend_search_path(&self, path: &str) {
        unsafe {
            ffi::gtk_source_style_scheme_manager_prepend_search_path(
                self.to_glib_none().0,
                path.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_set_search_path")]
    pub fn set_search_path(&self, path: &[&str]) {
        unsafe {
            ffi::gtk_source_style_scheme_manager_set_search_path(
                self.to_glib_none().0,
                path.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_style_scheme_manager_get_default")]
    #[doc(alias = "get_default")]
    #[allow(clippy::should_implement_trait)]
    pub fn default() -> StyleSchemeManager {
        assert_initialized_main_thread!();
        unsafe { from_glib_none(ffi::gtk_source_style_scheme_manager_get_default()) }
    }

    #[doc(alias = "scheme-ids")]
    pub fn connect_scheme_ids_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_scheme_ids_trampoline<F: Fn(&StyleSchemeManager) + 'static>(
            this: *mut ffi::GtkSourceStyleSchemeManager,
            _param_spec: glib::ffi::gpointer,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(&from_glib_borrow(this))
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"notify::scheme-ids\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_scheme_ids_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "search-path")]
    pub fn connect_search_path_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_search_path_trampoline<F: Fn(&StyleSchemeManager) + 'static>(
            this: *mut ffi::GtkSourceStyleSchemeManager,
            _param_spec: glib::ffi::gpointer,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(&from_glib_borrow(this))
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"notify::search-path\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_search_path_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl Default for StyleSchemeManager {
    fn default() -> Self {
        Self::new()
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`StyleSchemeManager`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct StyleSchemeManagerBuilder {
    builder: glib::object::ObjectBuilder<'static, StyleSchemeManager>,
}

impl StyleSchemeManagerBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn search_path(self, search_path: impl Into<glib::StrV>) -> Self {
        Self {
            builder: self.builder.property("search-path", search_path.into()),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`StyleSchemeManager`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> StyleSchemeManager {
        self.builder.build()
    }
}

impl fmt::Display for StyleSchemeManager {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("StyleSchemeManager")
    }
}
