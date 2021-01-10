use proc_macro::TokenStream;
use proc_macro2::TokenStream as TokenStream2;
use quote::quote;
use syn::{parse_macro_input, AttributeArgs, FnArg, Ident, ItemFn};

/// #[lua_function]
/// fn add(a: i64, b: i64) -> i64 {
///     a + b
/// }
///
/// Function `add` will be (conceptually) expanded to:
///
/// fn add(__args: (i64, i64)) -> i64 {
///     fn __do(a: i64, b: i64) -> i64 {
///         a + b
///     }
///     elonafoobar_log::trace!("'__native.{}.{}()' called", MODULE_NAME, "add");
///     __do(__args.0, __args.1)
/// }
#[proc_macro_attribute]
pub fn lua_function(args: TokenStream, item: TokenStream) -> TokenStream {
    let args = parse_macro_input!(args as AttributeArgs);
    let func = parse_macro_input!(item as ItemFn);
    let args = LuaFunctionArgs::from(args);
    lua_function_impl(func, args).into()
}

struct LuaFunctionArgs {
    log: bool,
}

impl Default for LuaFunctionArgs {
    fn default() -> Self {
        Self { log: true }
    }
}

impl From<AttributeArgs> for LuaFunctionArgs {
    fn from(raw_args: AttributeArgs) -> LuaFunctionArgs {
        use syn::{Lit, LitBool, Meta, MetaNameValue, NestedMeta};

        let mut args = LuaFunctionArgs::default();
        for arg in raw_args {
            if let NestedMeta::Meta(Meta::NameValue(MetaNameValue {
                path,
                eq_token: _,
                lit: Lit::Bool(LitBool { value, span: _ }),
            })) = arg
            {
                let path = path.get_ident();
                if path.map(|p| p == "log") == Some(true) {
                    args.log = value;
                } else {
                    panic!("#[lua_function] unknown argument");
                }
            } else {
                panic!("#[lua_function] invalid argument");
            }
        }
        args
    }
}

fn lua_function_impl(func: ItemFn, args: LuaFunctionArgs) -> TokenStream2 {
    let outer_fn_attributes = func.attrs;
    let outer_fn_attributes = quote! { #(#outer_fn_attributes)* };
    let outer_fn_visibility = func.vis;
    let outer_fn_name = func.sig.ident;

    let takes_lua_state = {
        let first_argument = func.sig.inputs.iter().next();
        first_argument.map(|a| match_argument_name(a, "lua")) == Some(true)
    };

    let outer_fn_arguments = {
        let argument_types = func
            .sig
            .inputs
            .iter()
            .flat_map(|arg| match arg {
                FnArg::Typed(arg) => Some(arg.ty.clone()),
                _ => None,
            })
            .collect::<Vec<_>>();
        if argument_types.is_empty() {
            quote! { __args: () }
        } else if takes_lua_state {
            let mut argument_types = argument_types.iter();
            let first = argument_types.next().unwrap();
            let rest = argument_types;
            quote! { __lua: #first, __args: ( #( #rest ),*, ) }
        } else {
            quote! { __args: ( #( #argument_types ),*, ) }
        }
    };

    let lua_fn_name = make_lua_function_name(&outer_fn_name);
    let fn_return_type = func.sig.output;
    let fn_arguments = {
        if takes_lua_state {
            let tuple_indice = make_index_sequence(func.sig.inputs.len() - 1);
            quote! { __lua, #( __args.#tuple_indice ),* }
        } else {
            let tuple_indice = make_index_sequence(func.sig.inputs.len());
            quote! { #( __args.#tuple_indice ),* }
        }
    };
    let inner_fn_block = func.block;
    let inner_fn_arguments = func.sig.inputs;
    let trace = if args.log {
        Some(quote! {
            ::elonafoobar_log::trace!(
                "'__native.{}.{}()' called",
                MODULE_NAME,
                #lua_fn_name,
            );
        })
    } else {
        None
    };

    quote! {
        #outer_fn_attributes
        #outer_fn_visibility
        fn #outer_fn_name(#outer_fn_arguments) #fn_return_type {
            #[inline]
            fn __do(#inner_fn_arguments) #fn_return_type #inner_fn_block

            #trace
            __do(#fn_arguments)
        }
    }
}

fn make_lua_function_name(rust_name: &Ident) -> String {
    let rust_name = rust_name.to_string();
    rust_name
        .strip_prefix("lua_")
        .map(ToString::to_string)
        .unwrap_or(rust_name)
}

fn make_index_sequence(n: usize) -> impl Iterator<Item = syn::Index> {
    (0..n).map(syn::Index::from)
}

fn match_argument_name(arg: &FnArg, name: &str) -> bool {
    use syn::{Pat, PatIdent, PatType};

    match arg {
        FnArg::Typed(PatType { pat, .. }) => match &**pat {
            Pat::Ident(PatIdent { ident, .. }) => *ident == name,
            _ => false,
        },
        _ => false,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_make_lua_function_name() {
        fn conv(rust_name: &str) -> String {
            make_lua_function_name(&Ident::new(rust_name, proc_macro2::Span::call_site()))
        }

        assert_eq!(conv("foo"), "foo");
        assert_eq!(conv("lua_foo"), "foo");
        assert_eq!(conv("lua_lua_foo"), "lua_foo");
        assert_eq!(conv("foo_lua_bar"), "foo_lua_bar");
    }
}
