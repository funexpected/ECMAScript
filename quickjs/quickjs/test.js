let start = Date.now();
let steps = 100000;
class V2 {
	constructor(x, y) {
		this.x = 0;
		this.y = 0;
		this.x = x;
		this.y = y;
	}
	add(v) {
		this.x += v.x;
		this.y += v.y;
		return this;
	}
}

start = Date.now();
let v2 = new V2(0, 0);
let v3 = new V2(0, 0);
steps = 100000;
while (steps > 0) {
    v2 = v2.add(new V2(Math.random() - 0.5, Math.random() - 0.5));
    //v2 = v2.add(v3)
    steps -= 1;
}
console.log("Time to 100000 iterations (own implementation):", Date.now() - start);


start = Date.now();
let vi = 0.0;
steps = 100000;
while (steps > 0) {
    // v2 = v2.add(new V2(Math.random() - 0.5, Math.random() - 0.5))
    vi += Math.random() - 0.5;
    steps -= 1;
}
console.log("Time to 100000 iterations (floats):", Date.now() - start);

start = Date.now();
let va = [0, 0];
steps = 100000;
while (steps > 0) {
    let va1 = [Math.random() - 0.5, Math.random() - 0.5];
    va = [va[0] + va1[0], va[1] + va1[1]]
    steps -= 1;
}
console.log("Time to 100000 iterations (arrays):", Date.now() - start);

start = Date.now();
let vb = Number(0);
steps = 100000;
while (steps > 0) {
    // v2 = v2.add(new V2(Math.random() - 0.5, Math.random() - 0.5))
    vb += Number(Math.random() - 0.5);
    steps -= 1;
}
console.log("Time to 100000 iterations (bigints):", Date.now() - start);

function test_values() {
    start = Date.now();
    let v4 = Vector2(0, 0);
    let attr = 0;
    steps = 100000;
    while (steps > 0) {
        v4 = v4.add(Vector2(Math.random() - 0.5, Math.random() - 0.5));
        attr = v4.x;
        //v2 = v2.add(v3)
        steps -= 1;
        // if (steps < 500) {
        //     v4 = v4.mult(21);
        // }
    }
    console.log("Time to 100000 iterations (value based):", Date.now() - start);
}
test_values();

function test_free() {
    let v = Vector2(0.2, 0.25);
    console.log("I'm Vector2", v.x, v.y);
}
console.log("Entring test_free()")
test_free();
console.log("Exited test_free()")