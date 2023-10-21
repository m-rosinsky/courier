extern crate colored;
use colored::*;

/// This enum enumerates the error types that courier can throw.
pub enum CourierErrorType {
    FileError,
    UnknownSymbol,
}

/// This is a private function that maps error types to strings.
fn get_err_type_string(err_type: &CourierErrorType) -> &'static str {
    match err_type {
        CourierErrorType::FileError => "File Error",
        CourierErrorType::UnknownSymbol => "Unknown Symbol",
    }
}

/// This struct defines the error class, which tracks various properties
/// for error reporting.
pub struct CourierError {
    pub err_type: CourierErrorType,
    pub line_num: u32,
    pub col_num: u32,
    pub msg: String,
}

impl CourierError {

/// This function reports an error to stderr.
pub fn report(&self) {
    eprint!("{} ", "Error".red());
    if self.line_num != 0 {
        eprint!("[{}:{}] ", self.line_num, self.col_num);
    }
    eprint!("{}", get_err_type_string(&self.err_type));
    if !self.msg.is_empty() {
        eprint!(": {}", self.msg);
    }
    eprint!("\n");
}

}
