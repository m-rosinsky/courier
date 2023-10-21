use crate::error::{self, CourierError};

/// This enum enumerates the different types of tokens for the lexer to
/// generate.
enum TokenType {
    TokenSymbol,
    TokenOperator,
    TokenNumeric,
    TokenDelimiter,
    TokenCtrl,
}

/// This struct represents a token created by the lexer.
pub struct Token {
    line_num: u32,
    col_num: u32,
    token: String,
    token_type: TokenType,
}

/// This struct defines a lexer context.
pub struct Lexer {
    token: String,
    line_num: u32,
    line_idx: u32,

    /// The table holding each token.
    pub table: Vec<Token>,
}

impl Lexer {
    /// This function instantiates a new Lexer object.
    pub fn new() -> Lexer {
        Lexer {
            token: String::new(),
            line_num: 1,
            line_idx: 0,
            table: Vec::new(),
        }
    }

    /// This function performs lexical analysis on a single file with
    /// a given path.
    /// 
    /// # Arguments:
    /// 
    /// * `path` - The file path
    pub fn lex_file(&self, path: &str) -> Result<(), error::CourierError> {
        let file = std::fs::File::open(path)
            .map_err(|e| CourierError{
                err_type: error::CourierErrorType::FileError,
                line_num: 0,
                col_num: 0,
                msg: String::from(format!("Failed to open file '{path}' ({})", e.to_string())),
            })?;

        Ok(())
    }
}
