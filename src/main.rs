/*!
 * @file src/main.rs
 *
 * @brief This file containts the main function of the program.
 */

extern crate clap;

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

    println!("Input file specified: '{}'", input_file);
}

/***   end of file   ***/
