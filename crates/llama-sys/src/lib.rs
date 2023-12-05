#![no_std]

use core::ffi;

extern "C" {
    pub fn bindings_init(numa_aware: bool);

    pub fn bindings_clip_model_open(
        path: *const ffi::c_char,
        verbosity: ffi::c_int,
    ) -> *mut ffi::c_void;
    pub fn bindings_clip_model_drop(model: *mut ffi::c_void);

    pub fn bindings_model_open(
        path: *const ffi::c_char,
        options: *const ffi::c_void,
    ) -> *mut ffi::c_void;
    pub fn bindings_model_new_session(
        model: *const ffi::c_void,
        options: *const ffi::c_void,
    ) -> *mut ffi::c_void;
    pub fn bindings_model_drop(model: *mut ffi::c_void);

    pub fn bindings_model_options_new() -> *mut ffi::c_void;
    pub fn bindings_model_options_drop(options: *mut ffi::c_void);
    pub fn bindings_model_options_gpu_layers(options: *const ffi::c_void) -> i32;
    pub fn bindings_model_options_set_gpu_layers(options: *mut ffi::c_void, value: i32);

    pub fn bindings_session_options_new() -> *mut ffi::c_void;
    pub fn bindings_session_options_drop(options: *mut ffi::c_void);

    pub fn bindings_session_drop(options: *mut ffi::c_void);
}
