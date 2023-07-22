// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::{SnippetChunk, SnippetContext};
use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
#[cfg(any(feature = "v5_6", feature = "dox"))]
#[cfg_attr(feature = "dox", doc(cfg(feature = "v5_6")))]
use std::ptr;
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceSnippet")]
    pub struct Snippet(Object<ffi::GtkSourceSnippet, ffi::GtkSourceSnippetClass>);

    match fn {
        type_ => || ffi::gtk_source_snippet_get_type(),
    }
}

impl Snippet {
    #[doc(alias = "gtk_source_snippet_new")]
    pub fn new(trigger: Option<&str>, language_id: Option<&str>) -> Snippet {
        assert_initialized_main_thread!();
        unsafe {
            from_glib_full(ffi::gtk_source_snippet_new(
                trigger.to_glib_none().0,
                language_id.to_glib_none().0,
            ))
        }
    }

    #[cfg(any(feature = "v5_6", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "v5_6")))]
    #[doc(alias = "gtk_source_snippet_new_parsed")]
    pub fn new_parsed(text: &str) -> Result<Snippet, glib::Error> {
        assert_initialized_main_thread!();
        unsafe {
            let mut error = ptr::null_mut();
            let ret = ffi::gtk_source_snippet_new_parsed(text.to_glib_none().0, &mut error);
            if error.is_null() {
                Ok(from_glib_full(ret))
            } else {
                Err(from_glib_full(error))
            }
        }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`Snippet`] objects.
    ///
    /// This method returns an instance of [`SnippetBuilder`](crate::builders::SnippetBuilder) which can be used to create [`Snippet`] objects.
    pub fn builder() -> SnippetBuilder {
        SnippetBuilder::new()
    }

    #[doc(alias = "gtk_source_snippet_add_chunk")]
    pub fn add_chunk(&self, chunk: &SnippetChunk) {
        unsafe {
            ffi::gtk_source_snippet_add_chunk(self.to_glib_none().0, chunk.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_snippet_copy")]
    #[must_use]
    pub fn copy(&self) -> Snippet {
        unsafe { from_glib_full(ffi::gtk_source_snippet_copy(self.to_glib_none().0)) }
    }

    #[doc(alias = "gtk_source_snippet_get_context")]
    #[doc(alias = "get_context")]
    pub fn context(&self) -> Option<SnippetContext> {
        unsafe { from_glib_none(ffi::gtk_source_snippet_get_context(self.to_glib_none().0)) }
    }

    #[doc(alias = "gtk_source_snippet_get_description")]
    #[doc(alias = "get_description")]
    pub fn description(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_get_description(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_get_focus_position")]
    #[doc(alias = "get_focus_position")]
    pub fn focus_position(&self) -> i32 {
        unsafe { ffi::gtk_source_snippet_get_focus_position(self.to_glib_none().0) }
    }

    #[doc(alias = "gtk_source_snippet_get_language_id")]
    #[doc(alias = "get_language_id")]
    pub fn language_id(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_get_language_id(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_get_n_chunks")]
    #[doc(alias = "get_n_chunks")]
    pub fn n_chunks(&self) -> u32 {
        unsafe { ffi::gtk_source_snippet_get_n_chunks(self.to_glib_none().0) }
    }

    #[doc(alias = "gtk_source_snippet_get_name")]
    #[doc(alias = "get_name")]
    pub fn name(&self) -> glib::GString {
        unsafe { from_glib_none(ffi::gtk_source_snippet_get_name(self.to_glib_none().0)) }
    }

    #[doc(alias = "gtk_source_snippet_get_nth_chunk")]
    #[doc(alias = "get_nth_chunk")]
    pub fn nth_chunk(&self, nth: u32) -> SnippetChunk {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_get_nth_chunk(
                self.to_glib_none().0,
                nth,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_get_trigger")]
    #[doc(alias = "get_trigger")]
    pub fn trigger(&self) -> Option<glib::GString> {
        unsafe { from_glib_none(ffi::gtk_source_snippet_get_trigger(self.to_glib_none().0)) }
    }

    #[doc(alias = "gtk_source_snippet_set_description")]
    pub fn set_description(&self, description: &str) {
        unsafe {
            ffi::gtk_source_snippet_set_description(
                self.to_glib_none().0,
                description.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_snippet_set_language_id")]
    pub fn set_language_id(&self, language_id: &str) {
        unsafe {
            ffi::gtk_source_snippet_set_language_id(
                self.to_glib_none().0,
                language_id.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_snippet_set_name")]
    pub fn set_name(&self, name: &str) {
        unsafe {
            ffi::gtk_source_snippet_set_name(self.to_glib_none().0, name.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_snippet_set_trigger")]
    pub fn set_trigger(&self, trigger: &str) {
        unsafe {
            ffi::gtk_source_snippet_set_trigger(self.to_glib_none().0, trigger.to_glib_none().0);
        }
    }

    pub fn buffer(&self) -> Option<gtk::TextBuffer> {
        glib::ObjectExt::property(self, "buffer")
    }

    #[doc(alias = "buffer")]
    pub fn connect_buffer_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_buffer_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::buffer\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_buffer_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "description")]
    pub fn connect_description_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_description_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::description\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_description_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "focus-position")]
    pub fn connect_focus_position_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_focus_position_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::focus-position\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_focus_position_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "language-id")]
    pub fn connect_language_id_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_language_id_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::language-id\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_language_id_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "name")]
    pub fn connect_name_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_name_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::name\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_name_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "trigger")]
    pub fn connect_trigger_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_trigger_trampoline<F: Fn(&Snippet) + 'static>(
            this: *mut ffi::GtkSourceSnippet,
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
                b"notify::trigger\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_trigger_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl Default for Snippet {
    fn default() -> Self {
        glib::object::Object::new::<Self>()
    }
}

impl fmt::Display for Snippet {
    #[inline]
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str(&self.name())
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`Snippet`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct SnippetBuilder {
    builder: glib::object::ObjectBuilder<'static, Snippet>,
}

impl SnippetBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn description(self, description: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("description", description.into()),
        }
    }

    pub fn language_id(self, language_id: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("language-id", language_id.into()),
        }
    }

    pub fn name(self, name: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("name", name.into()),
        }
    }

    pub fn trigger(self, trigger: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("trigger", trigger.into()),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`Snippet`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> Snippet {
        self.builder.build()
    }
}