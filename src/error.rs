/*!
 * @file src/error.rs
 * 
 * @brief This file contains the implementation of the error module,
 *          for reporting errors within Courier code.
 */

extern crate colored;
use colored::*;

/**
 * @brief This enum defines error types in courier.
 */
pub enum CourierErrorType {
    UnknownSymbol,
}

/**
 * @brief This function maps an error type to its associated report string.
 * 
 * @param[in] err_type The error type to map.
 */
fn get_err_type_string(err_type: &CourierErrorType) -> &'static str {
    match err_type {
        CourierErrorType::UnknownSymbol => "Unknown Symbol",
    }
}

/**
 * @brief This struct defines an error type.
 * 
 * @param err_type The type of error.
 * @param line_num The line number the error occurred on.
 * @param col_num The column number the error occurred on.
 * @param msg The optional message associated with the error.
 */
pub struct CourierError {
    pub err_type: CourierErrorType,
    pub line_num: u32,
    pub col_num: u32,
    pub msg: String,
}

impl CourierError {

/**
 * @brief This function reports the error to stderr.
 */
pub fn report(&self) {
    eprint!("{} [{}:{}] ", "Error".red(), self.line_num, self.col_num);
    eprint!("{}", get_err_type_string(&self.err_type));
    if !self.msg.is_empty() {
        eprint!(": {}", self.msg);
    }
    eprint!("\n");
}

}

/***   end of file   ***/
