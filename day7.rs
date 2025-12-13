use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;

fn main() {
    let f = File::open("day7.txt").unwrap();
    let matrix: Vec<Vec<i8>> = parse(f);

    println!("Solution to part 1: {}", problem1(&matrix));
    println!("Solution to part 2: {}", problem2(&matrix));
}

fn parse(file: File) -> Vec<Vec<i8>> {
    let reader = BufReader::new(file);
    let mut matrix: Vec<Vec<i8>> = vec![];

    for line_ in reader.lines() {
        let line = line_.unwrap();
        let mut row: Vec<i8> = vec![];

        for c in line.chars() {
            let point: i8;
            match c {
                'S' => point = 1,
                '^' => point = -1,
                _   => point = 0,
            }
            row.push(point);
        }
        matrix.push(row);
    }

    return matrix;
}

fn problem1(matrix: &Vec<Vec<i8>>) -> u16 {
    let mut splits: u16 = 0;
    let mut beams: Vec<Vec<i8>> = matrix.clone();

    for i in 1..beams.len() {
        for j in 0..beams[i].len() {
            match beams[i][j] {
                0 => {
                    if beams[i - 1][j] == 1 {
                        beams[i][j] = 1;
                    } 
                },
                -1 => {
                    if beams[i - 1][j] == 1 {
                        splits += 1;
                        beams[i][j - 1] = 1;
                        beams[i][j + 1] = 1;
                    }
                }
                _ => {}
            }
        }
    }

    return splits;
}

fn problem2(matrix: &Vec<Vec<i8>>) -> u64 {
    let mut timelines: u64 = 0;

    let mut beams: Vec<Vec<i128>> = matrix
        .iter()
        .map(|row| row.iter().map(|&x| x as i128).collect())
        .collect();

    // Pascals triangle variation
    for i in 1..beams.len() {
        for j in 0..beams[i].len() {
            if beams[i][j] == -1 {
                if beams[i - 1][j] > 0 {
                    beams[i][j - 1] += beams[i - 1][j];
                    beams[i][j + 1] += beams[i - 1][j];
                }
            } else {
                if beams[i - 1][j] > 0 {
                    beams[i][j] += beams[i - 1][j];
                }
            }
        }
    }

    let last = beams.len() - 1;
    for i in 0..beams[last].len() {
        timelines += beams[last][i] as u64;
    }

    return timelines;
}
