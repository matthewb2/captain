// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use crate::{CompletionCell, CompletionContext, CompletionProposal};
use glib::{prelude::*, translate::*};
use std::{boxed::Box as Box_, fmt, pin::Pin, ptr};

glib::wrapper! {
    #[doc(alias = "GtkSourceCompletionProvider")]
    pub struct CompletionProvider(Interface<ffi::GtkSourceCompletionProvider, ffi::GtkSourceCompletionProviderInterface>);

    match fn {
        type_ => || ffi::gtk_source_completion_provider_get_type(),
    }
}

impl CompletionProvider {
    pub const NONE: Option<&'static CompletionProvider> = None;
}

pub trait CompletionProviderExt: 'static {
    #[doc(alias = "gtk_source_completion_provider_activate")]
    fn activate(&self, context: &CompletionContext, proposal: &impl IsA<CompletionProposal>);

    #[doc(alias = "gtk_source_completion_provider_display")]
    fn display(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
        cell: &CompletionCell,
    );

    #[doc(alias = "gtk_source_completion_provider_get_priority")]
    #[doc(alias = "get_priority")]
    fn priority(&self, context: &CompletionContext) -> i32;

    #[doc(alias = "gtk_source_completion_provider_get_title")]
    #[doc(alias = "get_title")]
    fn title(&self) -> Option<glib::GString>;

    #[doc(alias = "gtk_source_completion_provider_is_trigger")]
    fn is_trigger(&self, iter: &gtk::TextIter, ch: char) -> bool;

    #[doc(alias = "gtk_source_completion_provider_key_activates")]
    fn key_activates(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
        keyval: u32,
        state: gdk::ModifierType,
    ) -> bool;

    #[doc(alias = "gtk_source_completion_provider_list_alternates")]
    fn list_alternates(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
    ) -> Vec<CompletionProposal>;

    #[doc(alias = "gtk_source_completion_provider_populate_async")]
    fn populate_async<P: FnOnce(Result<gio::ListModel, glib::Error>) + 'static>(
        &self,
        context: &CompletionContext,
        cancellable: Option<&impl IsA<gio::Cancellable>>,
        callback: P,
    );

    fn populate_future(
        &self,
        context: &CompletionContext,
    ) -> Pin<Box_<dyn std::future::Future<Output = Result<gio::ListModel, glib::Error>> + 'static>>;

    #[doc(alias = "gtk_source_completion_provider_refilter")]
    fn refilter(&self, context: &CompletionContext, model: &impl IsA<gio::ListModel>);
}

impl<O: IsA<CompletionProvider>> CompletionProviderExt for O {
    fn activate(&self, context: &CompletionContext, proposal: &impl IsA<CompletionProposal>) {
        unsafe {
            ffi::gtk_source_completion_provider_activate(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
                proposal.as_ref().to_glib_none().0,
            );
        }
    }

    fn display(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
        cell: &CompletionCell,
    ) {
        unsafe {
            ffi::gtk_source_completion_provider_display(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
                proposal.as_ref().to_glib_none().0,
                cell.to_glib_none().0,
            );
        }
    }

    fn priority(&self, context: &CompletionContext) -> i32 {
        unsafe {
            ffi::gtk_source_completion_provider_get_priority(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
            )
        }
    }

    fn title(&self) -> Option<glib::GString> {
        unsafe {
            from_glib_full(ffi::gtk_source_completion_provider_get_title(
                self.as_ref().to_glib_none().0,
            ))
        }
    }

    fn is_trigger(&self, iter: &gtk::TextIter, ch: char) -> bool {
        unsafe {
            from_glib(ffi::gtk_source_completion_provider_is_trigger(
                self.as_ref().to_glib_none().0,
                iter.to_glib_none().0,
                ch.into_glib(),
            ))
        }
    }

    fn key_activates(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
        keyval: u32,
        state: gdk::ModifierType,
    ) -> bool {
        unsafe {
            from_glib(ffi::gtk_source_completion_provider_key_activates(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
                proposal.as_ref().to_glib_none().0,
                keyval,
                state.into_glib(),
            ))
        }
    }

    fn list_alternates(
        &self,
        context: &CompletionContext,
        proposal: &impl IsA<CompletionProposal>,
    ) -> Vec<CompletionProposal> {
        unsafe {
            FromGlibPtrContainer::from_glib_full(
                ffi::gtk_source_completion_provider_list_alternates(
                    self.as_ref().to_glib_none().0,
                    context.to_glib_none().0,
                    proposal.as_ref().to_glib_none().0,
                ),
            )
        }
    }

    fn populate_async<P: FnOnce(Result<gio::ListModel, glib::Error>) + 'static>(
        &self,
        context: &CompletionContext,
        cancellable: Option<&impl IsA<gio::Cancellable>>,
        callback: P,
    ) {
        let main_context = glib::MainContext::ref_thread_default();
        let is_main_context_owner = main_context.is_owner();
        let has_acquired_main_context = (!is_main_context_owner)
            .then(|| main_context.acquire().ok())
            .flatten();
        assert!(
            is_main_context_owner || has_acquired_main_context.is_some(),
            "Async operations only allowed if the thread is owning the MainContext"
        );

        let user_data: Box_<glib::thread_guard::ThreadGuard<P>> =
            Box_::new(glib::thread_guard::ThreadGuard::new(callback));
        unsafe extern "C" fn populate_async_trampoline<
            P: FnOnce(Result<gio::ListModel, glib::Error>) + 'static,
        >(
            _source_object: *mut glib::gobject_ffi::GObject,
            res: *mut gio::ffi::GAsyncResult,
            user_data: glib::ffi::gpointer,
        ) {
            let mut error = ptr::null_mut();
            let ret = ffi::gtk_source_completion_provider_populate_finish(
                _source_object as *mut _,
                res,
                &mut error,
            );
            let result = if error.is_null() {
                Ok(from_glib_full(ret))
            } else {
                Err(from_glib_full(error))
            };
            let callback: Box_<glib::thread_guard::ThreadGuard<P>> =
                Box_::from_raw(user_data as *mut _);
            let callback: P = callback.into_inner();
            callback(result);
        }
        let callback = populate_async_trampoline::<P>;
        unsafe {
            ffi::gtk_source_completion_provider_populate_async(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
                cancellable.map(|p| p.as_ref()).to_glib_none().0,
                Some(callback),
                Box_::into_raw(user_data) as *mut _,
            );
        }
    }

    fn populate_future(
        &self,
        context: &CompletionContext,
    ) -> Pin<Box_<dyn std::future::Future<Output = Result<gio::ListModel, glib::Error>> + 'static>>
    {
        let context = context.clone();
        Box_::pin(gio::GioFuture::new(self, move |obj, cancellable, send| {
            obj.populate_async(&context, Some(cancellable), move |res| {
                send.resolve(res);
            });
        }))
    }

    fn refilter(&self, context: &CompletionContext, model: &impl IsA<gio::ListModel>) {
        unsafe {
            ffi::gtk_source_completion_provider_refilter(
                self.as_ref().to_glib_none().0,
                context.to_glib_none().0,
                model.as_ref().to_glib_none().0,
            );
        }
    }
}

impl fmt::Display for CompletionProvider {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("CompletionProvider")
    }
}
