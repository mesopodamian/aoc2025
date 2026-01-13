import { readFileSync } from "node:fs";

const input = readFileSync("input.txt", "utf8");

const rangesStr = input.split(",");
const ranges = [];

for (let i = 0; i < rangesStr.length; i++) {
    let range = rangesStr[i].split("-").map(Number);
    ranges.push(range);
}

let result = 0;

for (let i = 0; i < ranges.length; i++) {
    const [start, end] = ranges[i];
    for (let j = start; j <= end; j++) {
        let str = j.toString();
        if (str.length % 2 === 0) {
            let left = str.slice(0, str.length / 2);
            let right = str.slice(str.length / 2);
            if (left === right) {
                result += j;
            }
        }
    }
}

console.log("What do you get if you add up all of the invalid IDs?", result);
