// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::View;
use glib::{prelude::*, translate::*};
use std::fmt;

glib::wrapper! {
    #[doc(alias = "GtkSourceIndenter")]
    pub struct Indenter(Interface<ffi::GtkSourceIndenter, ffi::GtkSourceIndenterInterface>);

    match fn {
        type_ => || ffi::gtk_source_indenter_get_type(),
    }
}

impl Indenter {
    pub const NONE: Option<&'static Indenter> = None;
}

pub trait IndenterExt: 'static {
    //#[doc(alias = "gtk_source_indenter_indent")]
    //fn indent(&self, view: &impl IsA<View>, iter: /*Unimplemented*/gtk::TextIter);

    #[doc(alias = "gtk_source_indenter_is_trigger")]
    fn is_trigger(
        &self,
        view: &impl IsA<View>,
        location: &gtk::TextIter,
        state: gdk::ModifierType,
        keyval: u32,
    ) -> bool;
}

impl<O: IsA<Indenter>> IndenterExt for O {
    //fn indent(&self, view: &impl IsA<View>, iter: /*Unimplemented*/gtk::TextIter) {
    //    unsafe { TODO: call ffi:gtk_source_indenter_indent() }
    //}

    fn is_trigger(
        &self,
        view: &impl IsA<View>,
        location: &gtk::TextIter,
        state: gdk::ModifierType,
        keyval: u32,
    ) -> bool {
        unsafe {
            from_glib(ffi::gtk_source_indenter_is_trigger(
                self.as_ref().to_glib_none().0,
                view.as_ref().to_glib_none().0,
                location.to_glib_none().0,
                state.into_glib(),
                keyval,
            ))
        }
    }
}

impl fmt::Display for Indenter {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("Indenter")
    }
}