use std::collections::HashMap;
use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let n = parse_input!(input_line, i32);
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let m = parse_input!(input_line, i32);

    let mut signals = HashMap::new();
    for _ in 0..n as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split(" ").collect::<Vec<_>>();
        let input_name = inputs[0].trim().to_string();
        let input_signal = inputs[1].trim().to_string();

        signals.insert(input_name, input_signal);
    }
    for _ in 0..m as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split(" ").collect::<Vec<_>>();
        let output_name = inputs[0].trim().to_string();
        let _type = inputs[1].trim().to_string();
        let input_name_1 = inputs[2].trim().to_string();
        let input_name_2 = inputs[3].trim().to_string();

        let input_signal_1 = signals.get(&input_name_1).unwrap();
        let input_signal_2 = signals.get(&input_name_2).unwrap();

        let bool_signal_1: Vec<bool> = input_signal_1.chars().map(|c| {c == '-'}).collect();
        let bool_signal_2: Vec<bool> = input_signal_2.chars().map(|c| {c == '-'}).collect();

        let output: String = bool_signal_1.iter()
            .zip(&bool_signal_2)
            .map(|(b1, b2)| {
                match _type.as_str() {
                    "AND" => *b1 && *b2,
                    "OR" => *b1 || *b2,
                    "XOR" => *b1 != *b2,
                    "NAND" => !(*b1 && *b2),
                    "NOR" => !(*b1 || *b2),
                    "NXOR" => {*b1 == *b2},
                    _ => panic!("Unsupported gate")
                }
            })
            .map(|b| {
                if(b) {'-'} else { '_' }
            }).collect();

        println!("{output_name} {output}")

    }
}
