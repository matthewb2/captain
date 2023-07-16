// This file was generated by gir (https://github.com/gtk-rs/gir)
// from
// from gir-files (https://github.com/gtk-rs/gir-files.git)
// DO NOT EDIT

use glib::{
    prelude::*,
    signal::{connect_raw, SignalHandlerId},
    translate::*,
};
use std::{boxed::Box as Box_, fmt, mem::transmute};

glib::wrapper! {
    #[doc(alias = "GtkSourceTag")]
    pub struct Tag(Object<ffi::GtkSourceTag, ffi::GtkSourceTagClass>) @extends gtk::TextTag;

    match fn {
        type_ => || ffi::gtk_source_tag_get_type(),
    }
}

impl Tag {
    pub const NONE: Option<&'static Tag> = None;

    #[doc(alias = "gtk_source_tag_new")]
    pub fn new(name: Option<&str>) -> Tag {
        assert_initialized_main_thread!();
        unsafe {
            gtk::TextTag::from_glib_full(ffi::gtk_source_tag_new(name.to_glib_none().0))
                .unsafe_cast()
        }
    }

    // rustdoc-stripper-ignore-next
    /// Creates a new builder-pattern struct instance to construct [`Tag`] objects.
    ///
    /// This method returns an instance of [`TagBuilder`](crate::builders::TagBuilder) which can be used to create [`Tag`] objects.
    pub fn builder() -> TagBuilder {
        TagBuilder::new()
    }
}

impl Default for Tag {
    fn default() -> Self {
        glib::object::Object::new::<Self>()
    }
}

// rustdoc-stripper-ignore-next
/// A [builder-pattern] type to construct [`Tag`] objects.
///
/// [builder-pattern]: https://doc.rust-lang.org/1.0.0/style/ownership/builders.html
#[must_use = "The builder must be built to be used"]
pub struct TagBuilder {
    builder: glib::object::ObjectBuilder<'static, Tag>,
}

impl TagBuilder {
    fn new() -> Self {
        Self {
            builder: glib::object::Object::builder(),
        }
    }

    pub fn draw_spaces(self, draw_spaces: bool) -> Self {
        Self {
            builder: self.builder.property("draw-spaces", draw_spaces),
        }
    }

    pub fn draw_spaces_set(self, draw_spaces_set: bool) -> Self {
        Self {
            builder: self.builder.property("draw-spaces-set", draw_spaces_set),
        }
    }

    pub fn accumulative_margin(self, accumulative_margin: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("accumulative-margin", accumulative_margin),
        }
    }

    pub fn allow_breaks(self, allow_breaks: bool) -> Self {
        Self {
            builder: self.builder.property("allow-breaks", allow_breaks),
        }
    }

    pub fn allow_breaks_set(self, allow_breaks_set: bool) -> Self {
        Self {
            builder: self.builder.property("allow-breaks-set", allow_breaks_set),
        }
    }

    pub fn background(self, background: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("background", background.into()),
        }
    }

    pub fn background_full_height(self, background_full_height: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("background-full-height", background_full_height),
        }
    }

    pub fn background_full_height_set(self, background_full_height_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("background-full-height-set", background_full_height_set),
        }
    }

    pub fn background_rgba(self, background_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self.builder.property("background-rgba", background_rgba),
        }
    }

    pub fn background_set(self, background_set: bool) -> Self {
        Self {
            builder: self.builder.property("background-set", background_set),
        }
    }

    pub fn direction(self, direction: gtk::TextDirection) -> Self {
        Self {
            builder: self.builder.property("direction", direction),
        }
    }

    pub fn editable(self, editable: bool) -> Self {
        Self {
            builder: self.builder.property("editable", editable),
        }
    }

    pub fn editable_set(self, editable_set: bool) -> Self {
        Self {
            builder: self.builder.property("editable-set", editable_set),
        }
    }

    pub fn fallback(self, fallback: bool) -> Self {
        Self {
            builder: self.builder.property("fallback", fallback),
        }
    }

    pub fn fallback_set(self, fallback_set: bool) -> Self {
        Self {
            builder: self.builder.property("fallback-set", fallback_set),
        }
    }

    pub fn family(self, family: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("family", family.into()),
        }
    }

    pub fn family_set(self, family_set: bool) -> Self {
        Self {
            builder: self.builder.property("family-set", family_set),
        }
    }

    pub fn font(self, font: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("font", font.into()),
        }
    }

    pub fn font_desc(self, font_desc: &pango::FontDescription) -> Self {
        Self {
            builder: self.builder.property("font-desc", font_desc),
        }
    }

    pub fn font_features(self, font_features: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("font-features", font_features.into()),
        }
    }

    pub fn font_features_set(self, font_features_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("font-features-set", font_features_set),
        }
    }

    pub fn foreground(self, foreground: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("foreground", foreground.into()),
        }
    }

    pub fn foreground_rgba(self, foreground_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self.builder.property("foreground-rgba", foreground_rgba),
        }
    }

    pub fn foreground_set(self, foreground_set: bool) -> Self {
        Self {
            builder: self.builder.property("foreground-set", foreground_set),
        }
    }

    pub fn indent(self, indent: i32) -> Self {
        Self {
            builder: self.builder.property("indent", indent),
        }
    }

    pub fn indent_set(self, indent_set: bool) -> Self {
        Self {
            builder: self.builder.property("indent-set", indent_set),
        }
    }

    pub fn insert_hyphens(self, insert_hyphens: bool) -> Self {
        Self {
            builder: self.builder.property("insert-hyphens", insert_hyphens),
        }
    }

    pub fn insert_hyphens_set(self, insert_hyphens_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("insert-hyphens-set", insert_hyphens_set),
        }
    }

    pub fn invisible(self, invisible: bool) -> Self {
        Self {
            builder: self.builder.property("invisible", invisible),
        }
    }

    pub fn invisible_set(self, invisible_set: bool) -> Self {
        Self {
            builder: self.builder.property("invisible-set", invisible_set),
        }
    }

    pub fn justification(self, justification: gtk::Justification) -> Self {
        Self {
            builder: self.builder.property("justification", justification),
        }
    }

    pub fn justification_set(self, justification_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("justification-set", justification_set),
        }
    }

    pub fn language(self, language: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("language", language.into()),
        }
    }

    pub fn language_set(self, language_set: bool) -> Self {
        Self {
            builder: self.builder.property("language-set", language_set),
        }
    }

    pub fn left_margin(self, left_margin: i32) -> Self {
        Self {
            builder: self.builder.property("left-margin", left_margin),
        }
    }

    pub fn left_margin_set(self, left_margin_set: bool) -> Self {
        Self {
            builder: self.builder.property("left-margin-set", left_margin_set),
        }
    }

    pub fn letter_spacing(self, letter_spacing: i32) -> Self {
        Self {
            builder: self.builder.property("letter-spacing", letter_spacing),
        }
    }

    pub fn letter_spacing_set(self, letter_spacing_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("letter-spacing-set", letter_spacing_set),
        }
    }

    #[cfg(any(feature = "gtk_v4_6", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "gtk_v4_6")))]
    pub fn line_height(self, line_height: f32) -> Self {
        Self {
            builder: self.builder.property("line-height", line_height),
        }
    }

    pub fn line_height_set(self, line_height_set: bool) -> Self {
        Self {
            builder: self.builder.property("line-height-set", line_height_set),
        }
    }

    pub fn name(self, name: impl Into<glib::GString>) -> Self {
        Self {
            builder: self.builder.property("name", name.into()),
        }
    }

    pub fn overline(self, overline: pango::Overline) -> Self {
        Self {
            builder: self.builder.property("overline", overline),
        }
    }

    pub fn overline_rgba(self, overline_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self.builder.property("overline-rgba", overline_rgba),
        }
    }

    pub fn overline_rgba_set(self, overline_rgba_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("overline-rgba-set", overline_rgba_set),
        }
    }

    pub fn overline_set(self, overline_set: bool) -> Self {
        Self {
            builder: self.builder.property("overline-set", overline_set),
        }
    }

    pub fn paragraph_background(self, paragraph_background: impl Into<glib::GString>) -> Self {
        Self {
            builder: self
                .builder
                .property("paragraph-background", paragraph_background.into()),
        }
    }

    pub fn paragraph_background_rgba(self, paragraph_background_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self
                .builder
                .property("paragraph-background-rgba", paragraph_background_rgba),
        }
    }

    pub fn paragraph_background_set(self, paragraph_background_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("paragraph-background-set", paragraph_background_set),
        }
    }

    pub fn pixels_above_lines(self, pixels_above_lines: i32) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-above-lines", pixels_above_lines),
        }
    }

    pub fn pixels_above_lines_set(self, pixels_above_lines_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-above-lines-set", pixels_above_lines_set),
        }
    }

    pub fn pixels_below_lines(self, pixels_below_lines: i32) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-below-lines", pixels_below_lines),
        }
    }

    pub fn pixels_below_lines_set(self, pixels_below_lines_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-below-lines-set", pixels_below_lines_set),
        }
    }

    pub fn pixels_inside_wrap(self, pixels_inside_wrap: i32) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-inside-wrap", pixels_inside_wrap),
        }
    }

    pub fn pixels_inside_wrap_set(self, pixels_inside_wrap_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("pixels-inside-wrap-set", pixels_inside_wrap_set),
        }
    }

    pub fn right_margin(self, right_margin: i32) -> Self {
        Self {
            builder: self.builder.property("right-margin", right_margin),
        }
    }

    pub fn right_margin_set(self, right_margin_set: bool) -> Self {
        Self {
            builder: self.builder.property("right-margin-set", right_margin_set),
        }
    }

    pub fn rise(self, rise: i32) -> Self {
        Self {
            builder: self.builder.property("rise", rise),
        }
    }

    pub fn rise_set(self, rise_set: bool) -> Self {
        Self {
            builder: self.builder.property("rise-set", rise_set),
        }
    }

    pub fn scale(self, scale: f64) -> Self {
        Self {
            builder: self.builder.property("scale", scale),
        }
    }

    pub fn scale_set(self, scale_set: bool) -> Self {
        Self {
            builder: self.builder.property("scale-set", scale_set),
        }
    }

    #[cfg(any(feature = "gtk_v4_6", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "gtk_v4_6")))]
    pub fn sentence(self, sentence: bool) -> Self {
        Self {
            builder: self.builder.property("sentence", sentence),
        }
    }

    pub fn sentence_set(self, sentence_set: bool) -> Self {
        Self {
            builder: self.builder.property("sentence-set", sentence_set),
        }
    }

    pub fn show_spaces(self, show_spaces: pango::ShowFlags) -> Self {
        Self {
            builder: self.builder.property("show-spaces", show_spaces),
        }
    }

    pub fn show_spaces_set(self, show_spaces_set: bool) -> Self {
        Self {
            builder: self.builder.property("show-spaces-set", show_spaces_set),
        }
    }

    pub fn size(self, size: i32) -> Self {
        Self {
            builder: self.builder.property("size", size),
        }
    }

    pub fn size_points(self, size_points: f64) -> Self {
        Self {
            builder: self.builder.property("size-points", size_points),
        }
    }

    pub fn size_set(self, size_set: bool) -> Self {
        Self {
            builder: self.builder.property("size-set", size_set),
        }
    }

    pub fn stretch(self, stretch: pango::Stretch) -> Self {
        Self {
            builder: self.builder.property("stretch", stretch),
        }
    }

    pub fn stretch_set(self, stretch_set: bool) -> Self {
        Self {
            builder: self.builder.property("stretch-set", stretch_set),
        }
    }

    pub fn strikethrough(self, strikethrough: bool) -> Self {
        Self {
            builder: self.builder.property("strikethrough", strikethrough),
        }
    }

    pub fn strikethrough_rgba(self, strikethrough_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self
                .builder
                .property("strikethrough-rgba", strikethrough_rgba),
        }
    }

    pub fn strikethrough_rgba_set(self, strikethrough_rgba_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("strikethrough-rgba-set", strikethrough_rgba_set),
        }
    }

    pub fn strikethrough_set(self, strikethrough_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("strikethrough-set", strikethrough_set),
        }
    }

    pub fn style(self, style: pango::Style) -> Self {
        Self {
            builder: self.builder.property("style", style),
        }
    }

    pub fn style_set(self, style_set: bool) -> Self {
        Self {
            builder: self.builder.property("style-set", style_set),
        }
    }

    pub fn tabs(self, tabs: &pango::TabArray) -> Self {
        Self {
            builder: self.builder.property("tabs", tabs),
        }
    }

    pub fn tabs_set(self, tabs_set: bool) -> Self {
        Self {
            builder: self.builder.property("tabs-set", tabs_set),
        }
    }

    #[cfg(any(feature = "gtk_v4_6", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "gtk_v4_6")))]
    pub fn text_transform(self, text_transform: pango::TextTransform) -> Self {
        Self {
            builder: self.builder.property("text-transform", text_transform),
        }
    }

    pub fn text_transform_set(self, text_transform_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("text-transform-set", text_transform_set),
        }
    }

    pub fn underline(self, underline: pango::Underline) -> Self {
        Self {
            builder: self.builder.property("underline", underline),
        }
    }

    pub fn underline_rgba(self, underline_rgba: &gdk::RGBA) -> Self {
        Self {
            builder: self.builder.property("underline-rgba", underline_rgba),
        }
    }

    pub fn underline_rgba_set(self, underline_rgba_set: bool) -> Self {
        Self {
            builder: self
                .builder
                .property("underline-rgba-set", underline_rgba_set),
        }
    }

    pub fn underline_set(self, underline_set: bool) -> Self {
        Self {
            builder: self.builder.property("underline-set", underline_set),
        }
    }

    pub fn variant(self, variant: pango::Variant) -> Self {
        Self {
            builder: self.builder.property("variant", variant),
        }
    }

    pub fn variant_set(self, variant_set: bool) -> Self {
        Self {
            builder: self.builder.property("variant-set", variant_set),
        }
    }

    pub fn weight(self, weight: i32) -> Self {
        Self {
            builder: self.builder.property("weight", weight),
        }
    }

    pub fn weight_set(self, weight_set: bool) -> Self {
        Self {
            builder: self.builder.property("weight-set", weight_set),
        }
    }

    #[cfg(any(feature = "gtk_v4_6", feature = "dox"))]
    #[cfg_attr(feature = "dox", doc(cfg(feature = "gtk_v4_6")))]
    pub fn word(self, word: bool) -> Self {
        Self {
            builder: self.builder.property("word", word),
        }
    }

    pub fn word_set(self, word_set: bool) -> Self {
        Self {
            builder: self.builder.property("word-set", word_set),
        }
    }

    pub fn wrap_mode(self, wrap_mode: gtk::WrapMode) -> Self {
        Self {
            builder: self.builder.property("wrap-mode", wrap_mode),
        }
    }

    pub fn wrap_mode_set(self, wrap_mode_set: bool) -> Self {
        Self {
            builder: self.builder.property("wrap-mode-set", wrap_mode_set),
        }
    }

    // rustdoc-stripper-ignore-next
    /// Build the [`Tag`].
    #[must_use = "Building the object from the builder is usually expensive and is not expected to have side effects"]
    pub fn build(self) -> Tag {
        self.builder.build()
    }
}

pub trait TagExt: 'static {
    #[doc(alias = "draw-spaces")]
    fn draws_spaces(&self) -> bool;

    #[doc(alias = "draw-spaces")]
    fn set_draw_spaces(&self, draw_spaces: bool);

    #[doc(alias = "draw-spaces-set")]
    fn draws_spaces_set(&self) -> bool;

    #[doc(alias = "draw-spaces-set")]
    fn set_draw_spaces_set(&self, draw_spaces_set: bool);

    #[doc(alias = "draw-spaces")]
    fn connect_draw_spaces_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId;

    #[doc(alias = "draw-spaces-set")]
    fn connect_draw_spaces_set_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId;
}

impl<O: IsA<Tag>> TagExt for O {
    fn draws_spaces(&self) -> bool {
        glib::ObjectExt::property(self.as_ref(), "draw-spaces")
    }

    fn set_draw_spaces(&self, draw_spaces: bool) {
        glib::ObjectExt::set_property(self.as_ref(), "draw-spaces", draw_spaces)
    }

    fn draws_spaces_set(&self) -> bool {
        glib::ObjectExt::property(self.as_ref(), "draw-spaces-set")
    }

    fn set_draw_spaces_set(&self, draw_spaces_set: bool) {
        glib::ObjectExt::set_property(self.as_ref(), "draw-spaces-set", draw_spaces_set)
    }

    fn connect_draw_spaces_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_draw_spaces_trampoline<P: IsA<Tag>, F: Fn(&P) + 'static>(
            this: *mut ffi::GtkSourceTag,
            _param_spec: glib::ffi::gpointer,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(Tag::from_glib_borrow(this).unsafe_cast_ref())
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"notify::draw-spaces\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_draw_spaces_trampoline::<Self, F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }

    fn connect_draw_spaces_set_notify<F: Fn(&Self) + 'static>(&self, f: F) -> SignalHandlerId {
        unsafe extern "C" fn notify_draw_spaces_set_trampoline<P: IsA<Tag>, F: Fn(&P) + 'static>(
            this: *mut ffi::GtkSourceTag,
            _param_spec: glib::ffi::gpointer,
            f: glib::ffi::gpointer,
        ) {
            let f: &F = &*(f as *const F);
            f(Tag::from_glib_borrow(this).unsafe_cast_ref())
        }
        unsafe {
            let f: Box_<F> = Box_::new(f);
            connect_raw(
                self.as_ptr() as *mut _,
                b"notify::draw-spaces-set\0".as_ptr() as *const _,
                Some(transmute::<_, unsafe extern "C" fn()>(
                    notify_draw_spaces_set_trampoline::<Self, F> as *const (),
                )),
                Box_::into_raw(f),
            )
        }
    }
}

impl fmt::Display for Tag {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str("Tag")
    }
}
