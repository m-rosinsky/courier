extern crate clap;
mod error;
mod lexer;

fn main() {
    // Configure clap for command line args.
    let matches = clap::App::new("Courier")
        .version("0.1.0")
        .author("Mike Rosinsky")
        .about("A network-focused interpreted language")
        .arg(clap::Arg::with_name("in_file")
            .help("The input file to execute")
            .value_name("FILE")
            .required(true))
        .get_matches();

    let input_file = matches.value_of("in_file")
        .expect("Input file is a required field");

    // Lex the input file.
    let l = lexer::Lexer::new();
    let _ = match l.lex_file(input_file) {
        Ok(()) => (),
        Err(e) => {
            e.report();
            std::process::exit(1);
        }
    };
}
