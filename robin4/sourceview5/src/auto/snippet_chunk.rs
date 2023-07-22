// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::SnippetContext;
use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceSnippetChunk")]
    pub struct SnippetChunk(Object<ffi::GtkSourceSnippetChunk, ffi::GtkSourceSnippetChunkClass>);

    match fn {
        type_ => || ffi::gtk_source_snippet_chunk_get_type(),
    }
}

impl SnippetChunk {
    #[doc(alias = "gtk_source_snippet_chunk_new")]
    pub fn new() -> SnippetChunk {
        assert_initialized_main_thread!();
        unsafe { from_glib_none(ffi::gtk_source_snippet_chunk_new()) }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`SnippetChunk`] objects.
    ///
    /// This method returns an instance of [`SnippetChunkBuilder`](crate::builders::SnippetChunkBuilder) which can be used to create [`SnippetChunk`] objects.
    pub fn builder() -> SnippetChunkBuilder {
        SnippetChunkBuilder::new()
    }

    #[doc(alias = "gtk_source_snippet_chunk_copy")]
    #[must_use]
    pub fn copy(&self) -> SnippetChunk {
        unsafe { from_glib_full(ffi::gtk_source_snippet_chunk_copy(self.to_glib_none().0)) }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_context")]
    #[doc(alias = "get_context")]
    pub fn context(&self) -> SnippetContext {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_chunk_get_context(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_focus_position")]
    #[doc(alias = "get_focus_position")]
    pub fn focus_position(&self) -> i32 {
        unsafe { ffi::gtk_source_snippet_chunk_get_focus_position(self.to_glib_none().0) }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_spec")]
    #[doc(alias = "get_spec")]
    pub fn spec(&self) -> Option<glib::GString> {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_chunk_get_spec(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_text")]
    #[doc(alias = "get_text")]
    pub fn text(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_chunk_get_text(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_text_set")]
    #[doc(alias = "get_text_set")]
    pub fn is_text_set(&self) -> bool {
        unsafe {
            from_glib(ffi::gtk_source_snippet_chunk_get_text_set(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_get_tooltip_text")]
    #[doc(alias = "get_tooltip_text")]
    pub fn tooltip_text(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_snippet_chunk_get_tooltip_text(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_context")]
    pub fn set_context(&self, context: &SnippetContext) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_context(
                self.to_glib_none().0,
                context.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_focus_position")]
    pub fn set_focus_position(&self, focus_position: i32) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_focus_position(self.to_glib_none().0, focus_position);
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_spec")]
    pub fn set_spec(&self, spec: &str) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_spec(self.to_glib_none().0, spec.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_text")]
    pub fn set_text(&self, text: &str) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_text(self.to_glib_none().0, text.to_glib_none().0);
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_text_set")]
    pub fn set_text_set(&self, text_set: bool) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_text_set(self.to_glib_none().0, text_set.into_glib());
        }
    }

    #[doc(alias = "gtk_source_snippet_chunk_set_tooltip_text")]
    pub fn set_tooltip_text(&self, tooltip_text: &str) {
        unsafe {
            ffi::gtk_source_snippet_chunk_set_tooltip_text(
                self.to_glib_none().0,
                tooltip_text.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "context")]
    pub fn connect_context_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_context_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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
                b"notify::context\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_context_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "focus-position")]
    pub fn connect_focus_position_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_focus_position_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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

    #[doc(alias = "spec")]
    pub fn connect_spec_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_spec_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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
                b"notify::spec\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_spec_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "text")]
    pub fn connect_text_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_text_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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
                b"notify::text\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_text_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "text-set")]
    pub fn connect_text_set_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_text_set_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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
                b"notify::text-set\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_text_set_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "tooltip-text")]
    pub fn connect_tooltip_text_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_tooltip_text_trampoline<F: Fn(&SnippetChunk) + 'static>(
            this: *mut ffi::GtkSourceSnippetChunk,
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
                b"notify::tooltip-text\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_tooltip_text_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl Default for SnippetChunk {
    fn default() -> Self {
        Self::new()
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`SnippetChunk`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct SnippetChunkBuilder {
    builder: glib::object::ObjectBuilder<'static, SnippetChunk>,
}

impl SnippetChunkBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn context(self, context: &SnippetContext) -> Self {
        Self {
            builder: self.builder.property("context", context.clone()),
        }
    }

    pub fn focus_position(self, focus_position: i32) -> Self {
        Self {
            builder: self.builder.property("focus-position", focus_position),
        }
    }

    pub fn spec(self, spec: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("spec", spec.into()),
        }
    }

    pub fn text(self, text: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("text", text.into()),
        }
    }

    pub fn text_set(self, text_set: bool) -> Self {
        Self {
            builder: self.builder.property("text-set", text_set),
        }
    }

    pub fn tooltip_text(self, tooltip_text: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("tooltip-text", tooltip_text.into()),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`SnippetChunk`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> SnippetChunk {
        self.builder.build()
    }
}

impl fmt::Display for SnippetChunk {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("SnippetChunk")
    }
}