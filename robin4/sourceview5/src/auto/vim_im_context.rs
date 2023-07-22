// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::View;
use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceVimIMContext")]
    pub struct VimIMContext(Object<ffi::GtkSourceVimIMContext, ffi::GtkSourceVimIMContextClass>) @extends gtk::IMContext;

    match fn {
        type_ => || ffi::gtk_source_vim_im_context_get_type(),
    }
}

impl VimIMContext {
    #[doc(alias = "gtk_source_vim_im_context_new")]
    pub fn new() -> VimIMContext {
        assert_initialized_main_thread!();
        unsafe {
            gtk::IMContext::from_glib_full(ffi::gtk_source_vim_im_context_new()).unsafe_cast()
        }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`VimIMContext`] objects.
    ///
    /// This method returns an instance of [`VimIMContextBuilder`](crate::builders::VimIMContextBuilder) which can be used to create [`VimIMContext`] objects.
    pub fn builder() -> VimIMContextBuilder {
        VimIMContextBuilder::new()
    }

    #[doc(alias = "gtk_source_vim_im_context_execute_command")]
    pub fn execute_command(&self, command: &str) {
        unsafe {
            ffi::gtk_source_vim_im_context_execute_command(
                self.to_glib_none().0,
                command.to_glib_none().0,
            );
        }
    }

    #[doc(alias = "gtk_source_vim_im_context_get_command_bar_text")]
    #[doc(alias = "get_command_bar_text")]
    pub fn command_bar_text(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_vim_im_context_get_command_bar_text(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "gtk_source_vim_im_context_get_command_text")]
    #[doc(alias = "get_command_text")]
    pub fn command_text(&self) -> glib::GString {
        unsafe {
            from_glib_none(ffi::gtk_source_vim_im_context_get_command_text(
                self.to_glib_none().0,
            ))
        }
    }

    #[doc(alias = "command-bar-text")]
    pub fn get_property_command_bar_text(&self) -> Option<glib::GString> {
        glib::ObjectExt::property(self, "command-bar-text")
    }

    #[doc(alias = "command-text")]
    pub fn get_property_command_text(&self) -> Option<glib::GString> {
        glib::ObjectExt::property(self, "command-text")
    }

    #[cfg(any(feature = "v5_4", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "v5_4")))]
    #[doc(alias = "edit")]
    pub fn connect_edit<F: Fn(&Self, &View, Option<&str>) + 'static>(
        &self,
        f: F,
    ) -> SignalHandlerId {
        unsafe extern "C" fn edit_trampoline<
            F: Fn(&VimIMContext, &View, Option<&str>) + 'static,
        >(
            this: *mut ffi::GtkSourceVimIMContext,
            view: *mut ffi::GtkSourceView,
            path: *mut libc::c_char,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(
                &from_glib_borrow(this),
                &from_glib_borrow(view),
                Option::<glib::GString>::from_glib_borrow(path)
                    .as_ref()
                    .as_ref()
                    .map(|s| s.as_str()),
            )
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"edit\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    edit_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[cfg(any(feature = "v5_4", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "v5_4")))]
    #[doc(alias = "execute-command")]
    pub fn connect_execute_command<F: Fn(&Self, &str) -> bool + 'static>(
        &self,
        f: F,
    ) -> SignalHandlerId {
        unsafe extern "C" fn execute_command_trampoline<
            F: Fn(&VimIMContext, &str) -> bool + 'static,
        >(
            this: *mut ffi::GtkSourceVimIMContext,
            command: *mut libc::c_char,
            f: glib::ffi::gpointer,
        ) -> glib::ffi::gboolean {
            let f: &F = &*(f as *const F);
            f(
                &from_glib_borrow(this),
                &glib::GString::from_glib_borrow(command),
            )
            .into_glib()
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"execute-command\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    execute_command_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[cfg(any(feature = "v5_4", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "v5_4")))]
    #[doc(alias = "format-text")]
    pub fn connect_format_text<F: Fn(&Self, &gtk::TextIter, &gtk::TextIter) + 'static>(
        &self,
        f: F,
    ) -> SignalHandlerId {
        unsafe extern "C" fn format_text_trampoline<
            F: Fn(&VimIMContext, &gtk::TextIter, &gtk::TextIter) + 'static,
        >(
            this: *mut ffi::GtkSourceVimIMContext,
            begin: *mut gtk::ffi::GtkTextIter,
            end: *mut gtk::ffi::GtkTextIter,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(
                &from_glib_borrow(this),
                &from_glib_borrow(begin),
                &from_glib_borrow(end),
            )
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"format-text\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    format_text_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[cfg(any(feature = "v5_4", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "v5_4")))]
    #[doc(alias = "write")]
    pub fn connect_write<F: Fn(&Self, &View, Option<&str>) + 'static>(
        &self,
        f: F,
    ) -> SignalHandlerId {
        unsafe extern "C" fn write_trampoline<
            F: Fn(&VimIMContext, &View, Option<&str>) + 'static,
        >(
            this: *mut ffi::GtkSourceVimIMContext,
            view: *mut ffi::GtkSourceView,
            path: *mut libc::c_char,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(
                &from_glib_borrow(this),
                &from_glib_borrow(view),
                Option::<glib::GString>::from_glib_borrow(path)
                    .as_ref()
                    .as_ref()
                    .map(|s| s.as_str()),
            )
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"write\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    write_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "command-bar-text")]
    pub fn connect_command_bar_text_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_command_bar_text_trampoline<F: Fn(&VimIMContext) + 'static>(
            this: *mut ffi::GtkSourceVimIMContext,
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
                b"notify::command-bar-text\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_command_bar_text_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    #[doc(alias = "command-text")]
    pub fn connect_command_text_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_command_text_trampoline<F: Fn(&VimIMContext) + 'static>(
            this: *mut ffi::GtkSourceVimIMContext,
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
                b"notify::command-text\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_command_text_trampoline::<F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl Default for VimIMContext {
    fn default() -> Self {
        Self::new()
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`VimIMContext`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct VimIMContextBuilder {
    builder: glib::object::ObjectBuilder<'static, VimIMContext>,
}

impl VimIMContextBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn input_hints(self, input_hints: gtk::InputHints) -> Self {
        Self {
            builder: self.builder.property("input-hints", input_hints),
        }
    }

    pub fn input_purpose(self, input_purpose: gtk::InputPurpose) -> Self {
        Self {
            builder: self.builder.property("input-purpose", input_purpose),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`VimIMContext`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> VimIMContext {
        self.builder.build()
    }
}

impl fmt::Display for VimIMContext {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("VimIMContext")
    }
}