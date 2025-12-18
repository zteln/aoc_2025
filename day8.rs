use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;
use std::collections::HashSet;

fn main() {
    let f = File::open("day8.txt").unwrap();
    let coords: Vec<Vec<u64>> = parse(f);

    println!("Solution to part 1: {}", problem1(&coords));
    println!("Solution to part 2: {}", problem2(&coords));
}

fn parse(file: File) -> Vec<Vec<u64>> {
    let reader = BufReader::new(file);
    let mut coords: Vec<Vec<u64>> = vec![];

    for line_ in reader.lines() {
        let line = line_.unwrap();
        let coord: Vec<u64> = line
            .split(",")
            .filter_map(|n| n.trim().parse().ok())
            .collect();

        coords.push(coord);
    }

    return coords;
}

fn problem1(coords: &Vec<Vec<u64>>) -> u64 {
    let mut result: u64 = 1;
    let mut dists: Vec<(f64, usize, usize)> = vec![];
    let mut sets: Vec<HashSet<usize>> = vec![];
    let mut sizes: Vec<usize> = vec![];

    for i in 0..coords.len() {
        for j in (i+1)..coords.len() {
            let p1: Vec<u64> = coords[i].clone();
            let p2: Vec<u64> = coords[j].clone();
            let dist: f64 = euclidean_distance(p1, p2);
            dists.push((dist, i, j));
        }
    }

    dists.sort_by(|a, b| a.0.partial_cmp(&b.0).unwrap());

    for (_, i, j) in dists.iter().take(1000) {
        let mut indices_to_merge: Vec<usize> = vec![];

        for (k, set) in sets.iter().enumerate() {
            if set.contains(i) || set.contains(j) {
                indices_to_merge.push(k);
            } 
        }

        let mut set: HashSet<usize> = HashSet::new();
        set.insert(*i);
        set.insert(*j);
        for idx in indices_to_merge.iter().rev() {
            let merged_set = sets.remove(*idx);
            set.extend(merged_set);
        }
        sets.push(set);
    }

    for set in sets.iter() {
        sizes.push(set.len());
    }

    sizes.sort();
    sizes.reverse();
    for size in sizes.iter().take(3) {
        result *= *size as u64;
    }

    return result;
}

fn problem2(coords: &Vec<Vec<u64>>) -> u64 {
    let mut sets: Vec<HashSet<usize>> = vec![];
    let mut dists: Vec<(f64, usize, usize)> = vec![];

    for i in 0..coords.len() {
        for j in (i+1)..coords.len() {
            let p1: Vec<u64> = coords[i].clone();
            let p2: Vec<u64> = coords[j].clone();
            let dist: f64 = euclidean_distance(p1, p2);
            dists.push((dist, i, j));
        }
    }

    dists.sort_by(|a, b| a.0.partial_cmp(&b.0).unwrap());

    // break when len(sets) == 1 and size(hashset) == len(coords) (input)
    loop {
        for (_, i, j) in dists.iter() {
            let mut indices_to_merge: Vec<usize> = vec![];
            for (k, set) in sets.iter().enumerate() {
                if set.contains(i) || set.contains(j) {
                    indices_to_merge.push(k);
                } 
            }

            let mut set: HashSet<usize> = HashSet::new();
            set.insert(*i);
            set.insert(*j);
            for idx in indices_to_merge.iter().rev() {
                let merged_set = sets.remove(*idx);
                set.extend(merged_set);
            }
            sets.push(set);

            if sets.len() == 1 && sets[0].len() == coords.len() {
                return coords[*i][0] * coords[*j][0];
            }
        }
    }
    // return 0;
}

fn euclidean_distance(p1: Vec<u64>, p2: Vec<u64>) -> f64 {
    let mut d_sqrd: f64 = 0.0;
    for i in 0..p1.len() {
        let diff = p1[i] as f64 - p2[i] as f64;
        d_sqrd += diff * diff;
    }

    return d_sqrd.sqrt();
}
