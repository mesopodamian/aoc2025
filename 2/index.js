import { readFileSync } from "node:fs";

const input = readFileSync("input.txt", "utf8");

const rangesStr = input.split(",");
const ranges = [];

for (let i = 0; i < rangesStr.length; i++) {
    let range = rangesStr[i].split("-").map(Number);
    ranges.push(range);
}

let result = 0;

// Part One

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

// Part Two

result = 0;
for (let i = 0; i < ranges.length; i++) {
    const [start, end] = ranges[i];
    for (let id = start; id <= end; id++) {
        let idStr = id.toString();
        let idLength = idStr.length;

        let isInvalid = false;

        // split ID into chunks
        for (let k = 1; k <= idLength; k++) {
            // k - scaning window size
            let isEven = idLength % k == 0;
            if (!isEven) continue;

            let chunks = chunkString(idStr, k);

            // check if all chunks are the same
            for (let x = 1; x <= chunks.length - 1; x++) {
                let prev = chunks[x - 1];
                let curr = chunks[x];

                if (prev === curr) {
                    isInvalid = true;
                } else {
                    isInvalid = false;
                    break; // check if all chunks are the same
                }
            }

            if (isInvalid) {
                result += id;
                break; // split ID into chunks
            }
        }
    }
}

// https://stackoverflow.com/questions/7033639/split-large-string-in-n-size-chunks-in-javascript
function chunkString(str, length) {
    return str.match(new RegExp(".{1," + length + "}", "g"));
}

console.log("What do you get if you add up all of the invalid IDs using these new rules?", result);
