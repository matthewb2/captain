// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::{SpaceLocationFlags, SpaceTypeFlags};
use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceSpaceDrawer")]
    pub struct SpaceDrawer(Object<ffi::GtkSourceSpaceDrawer, ffi::GtkSourceSpaceDrawerClass>);

    match fn {
        type_ => || ffi::gtk_source_space_drawer_get_type(),
    }
}

impl SpaceDrawer {
    #[doc(alias = "gtk_source_space_drawer_new")]
    pub fn new() -> SpaceDrawer {
        assert_initialized_main_thread!();
        unsafe { from_glib_full(ffi::gtk_source_space_drawer_new()) }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`SpaceDrawer`] objects.
    ///
    /// This method returns an instance of [`SpaceDrawerBuilder`](crate::builders::SpaceDrawerBuilder) which can be used to create [`SpaceDrawer`] objects.
    pub fn builder() -> SpaceDrawerBuilder {
        SpaceDrawerBuilder::new()
    }

    #[doc(alias = "gtk_source_space_drawer_bind_matrix_setting")]
    pub fn bind_matrix_setting(
        &self,
        settings: &impl IsA<gio::Settings>,
        key: &str,
        flags: gio::SettingsBindFlags,
    ) {
        unsafe {
            ffi::gtk_source_space_drawer_bind_matrix_setting(
                self.to_glib_none().0,
                settings.as_ref().to_glib_none().0,
                key.to_glib_none().0,
                flags.into_glib(),
            );
        }
    }

    #[doc(alias = "gtk_source_space_drawer_get_enable_matrix")]
    #[doc(alias = "get_enable_matrix")]
    pub fn enables_matrix(&self) -> bool {
        unsafe {
            from_glib(ffi::gtk_source_space_drawer_get_enable_matrix(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_space_drawer_get_matrix")]
    #[doc(alias = "get_matrix")]
    pub fn matrix(&self) -> glib::Variant {
        unsafe {
            from_glib_full(ffi::gtk_source_space_drawer_get_matrix(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_space_drawer_get_types_for_locations")]
    #[doc(alias = "get_types_for_locations")]
    pub fn types_for_locations(&self, locations: SpaceLocationFlags) -> SpaceTypeFlags {
        unsafe {
            from_glib(ffi::gtk_source_space_drawer_get_types_for_locations(
                self.to_glib_none().0,
                locations.into_glib(),
            ))
        }
    }

    #[doc(alias = "gtk_source_space_drawer_set_enable_matrix")]
    pub fn set_enable_matrix(&self, enable_matrix: bool) {
        unsafe {
            ffi::gtk_source_space_drawer_set_enable_matrix(
                self.to_glib_none().0,
                enable_matrix.into_glib(),
            );
        }
    }

    #[doc(alias = "gtk_source_space_drawer_set_matrix")]
    pub fn set_matrix(&self, matrix: Option<&glib::Variant>) {
        unsafe {
            ffi::gtk_source_space_drawer_set_matrix(self.to_glib_none().0, matrix.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_space_drawer_set_types_for_locations")]
    pub fn set_types_for_locations(&self, locations: SpaceLocationFlags, types: SpaceTypeFlags) {
        unsafe {
            ffi::gtk_source_space_drawer_set_types_for_locations(
                self.to_glib_none().0,
                locations.into_glib(),
                types.into_glib(),
            );
        }
    }

    #[doc(alias = "enable-matrix")]
    pub fn connect_enable_matrix_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_enable_matrix_trampoline<F: Fn(&SpaceDrawer) + 'static>(
            this: *mut ffi::GtkSourceSpaceDrawer,
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
                b"notify::enable-matrix\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_enable_matrix_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "matrix")]
    pub fn connect_matrix_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_matrix_trampoline<F: Fn(&SpaceDrawer) + 'static>(
            this: *mut ffi::GtkSourceSpaceDrawer,
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
                b"notify::matrix\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_matrix_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl Default for SpaceDrawer {
    fn default() -> Self {
        Self::new()
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`SpaceDrawer`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct SpaceDrawerBuilder {
    builder: glib::object::ObjectBuilder<'static, SpaceDrawer>,
}

impl SpaceDrawerBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn enable_matrix(self, enable_matrix: bool) -> Self {
        Self {
            builder: self.builder.property("enable-matrix", enable_matrix),
        }
    }

    pub fn matrix(self, matrix: &glib::Variant) -> Self {
        Self {
            builder: self.builder.property("matrix", matrix.clone()),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`SpaceDrawer`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> SpaceDrawer {
        self.builder.build()
    }
}

impl fmt::Display for SpaceDrawer {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("SpaceDrawer")
    }
}