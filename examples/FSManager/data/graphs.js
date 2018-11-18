function ce(t) {
	return document.createElement(t)
}
function ac(a, b) {
	a.appendChild(b)
}
function createGraph(b, t, w, h, l, m, d, f, j) {
	if (typeof b === "undefined" || !b) return null;
	if (typeof d === "undefined" || !d) d = false;
	w = (w > 360) ? w: 360;
	h = (h < 100) ? 100 : h;
	var k = new Array();
	var n = "black";
	var o = (typeof f === "undefined" && f) ? "yellow": f;
	var p = "#444";
	var q = (typeof j === "undefined" && j) ? null: j;
	var r = m;
	var s = 0;
	var u = 1;
	var x = l;
	var y = h + 20;
	b.style.display = "block";
	b.style.backgroundColor = "#eee";
	b.style.border = "1px solid " + p;
	b.style.padding = "5px";
	b.style.margin = "5px";
	b.style.width = (w + 2) + "px";
	var g = ce("canvas");
	g.style.border = "1px solid " + p;
	g.style.marginTop = "5px";
	g.width = w;
	g.height = y;
	var c = g.getContext("2d");
	var z = ce("span");
	z.innerText = "Scale: ";
	z.style.paddingLeft = "5px";
	var A = ce("input");
	A.type = "text";
	A.size = 3;
	A.value = u;
	A.onchange = function (e) {
		u = A.value
	};
	var B = ce("button");
	B.innerText = "-";
	B.onclick = function (e) {
		if (u > 1) u--;
		A.value = u
	};
	var C = ce("button");
	C.innerText = "+";
	C.onclick = function (e) {
		u++;
		A.value = parseInt(u)
	};
	var D = ce("span");
	D.innerText = "Offset: ";
	D.style.paddingLeft = "5px";
	var E = ce("input");
	E.type = "text";
	E.size = 5;
	E.value = x;
	E.onchange = function (e) {
		x = parseInt(E.value)
	};
	var F = ce("button");
	F.innerText = "-";
	F.onclick = function (e) {
		if (x > l) x--;
		E.value = x
	};
	var G = ce("button");
	G.innerText = "+";
	G.onclick = function (e) {
		if (x < m) x++;
		E.value = x
	};
	ac(b, z);
	ac(b, B);
	ac(b, A);
	ac(b, C);
	ac(b, D);
	ac(b, F);
	ac(b, E);
	ac(b, G);
	ac(b, ce("br"));
	ac(b, g);
	function scv(v) {
		if (v <= x) return 0;
		if (v > (((m - l) / u) + x)) return h;
		return Math.round((v - x) * (h / ((m - l) / u)))
	}
	g.add = function (v) {
		if (q) v = q(v);
		k.push(v);
		if (v < r) r = v;
		if (v > s) s = v;
		if (k.length > w) k.shift();
		c.canvas.width = w;
		c.lineWidth = 1;
		c.shadowBlur = 2;
		c.shadowColor = "black";
		c.fillStyle = p;
		c.fillRect(0, 0, w, 20);
		c.fillStyle = o;
		c.font = "14px Verdana";
		var a = t + ": " + (k[k.length - 1]) + " | Min: " + r + " | Max: " + s;
		c.fillText(a, 5, 15);
		c.fillStyle = n;
		c.fillRect(0, 20, w, y);
		c.strokeStyle = o;
		for (var i = 0; i < k.length; i++) {
			if (d) {
				c.moveTo(i, y);
				c.lineTo(i, y - scv(k[i]));
				c.stroke();
				continue
			}
			if (i === 0) {
				c.moveTo(0, y - scv(k[0]));
				c.lineTo(0, y - scv(k[0]));
				c.stroke()
			} else {
				c.moveTo((i - 1), y - scv(k[i - 1]));
				c.lineTo(i, y - scv(k[i]));
				c.stroke()
			}
		}
		c.fillStyle = o;
		c.font = "10px Verdana";
		c.fillText(x, 2, y - 5);
		c.fillText(Math.round((((m - l) / u) + x) * 10) / 10, 2, 30)
	};
	return g
}
function createDigiGraph(j, t, w, h, m, k) {
	if (typeof j === "undefined" || !j) return null;
	w = (w > 360) ? w: 360;
	h = (h < 20) ? 20 : h;
	var l = new Array();
	var n = "black";
	var o = (typeof k === "undefined" && k) ? "pink": k;
	var q = "#444";
	var r = 1;
	var u = h + 20;
	j.style.display = "block";
	j.style.backgroundColor = "#eee";
	j.style.border = "1px solid " + q;
	j.style.padding = "5px";
	j.style.margin = "5px";
	j.style.width = (w + 2) + "px";
	var g = ce("canvas");
	g.style.border = "1px solid " + q;
	g.style.marginTop = "5px";
	g.width = w;
	g.height = u;
	var c = g.getContext("2d");
	var x = ce("span");
	x.innerText = "Scale: ";
	x.style.paddingLeft = "5px";
	var y = ce("input");
	y.type = "text";
	y.size = 3;
	y.value = r;
	y.onchange = function (e) {
		r = y.value
	};
	var z = ce("button");
	z.innerText = "-";
	z.onclick = function (e) {
		if (r > 1) r--;
		y.value = r
	};
	var A = ce("button");
	A.innerText = "+";
	A.onclick = function (e) {
		r++;
		y.value = parseInt(r)
	};
	ac(j, x);
	ac(j, z);
	ac(j, y);
	ac(j, A);
	ac(j, ce("br"));
	ac(j, g);
	function gpos(p) {
		var a = Math.floor(((h - ((m.length - 1) * 2)) / m.length));
		var s = (p * 2) + (p * a);
		return [s, s + a]
	}
	function gact(i, p) {
		return ((l[i] & (1 << m[p])) !== 0)
	}
	var B = ["aqua", "yellow", "#FF4500", "#00FF7F", "orange", "cyan", "magenta", "#7FFF00", "#FAF0E6", "#00CED1", "#FFD700", "#EE82EE", "#00FF00", "#00BFFF", "#FF4500", "#EEE8AA", "#FF1493"];
	g.add = function (v) {
		l.push(v);
		if (l.length > w) l.shift();
		c.canvas.width = w;
		c.lineWidth = 1;
		c.shadowBlur = 2;
		c.shadowColor = "black";
		c.fillStyle = q;
		c.fillRect(0, 0, w, 20);
		c.fillStyle = o;
		c.font = "14px Verdana";
		c.fillText(t, 5, 15);
		c.fillStyle = n;
		c.fillRect(0, 20, w, u);
		c.strokeStyle = q;
		c.lineWidth = 1;
		c.shadowBlur = 0;
		c.shadowColor = "";
		for (var p = 0; p < m.length; p++) {
			var a = gpos(p);
			c.moveTo(0, 20 + a[1] + 1);
			c.lineTo(w, 20 + a[1] + 1);
			c.stroke()
		}
		c.shadowBlur = 2;
		c.font = "14px Verdana";
		var b = Math.round(w / r);
		var d = w - b - (w - l.length);
		if (d < 0) d = 0;
		for (var i = d; i < l.length; i++) {
			for (var p = 0; p < m.length; p++) {
				var a = gpos(p);
				var e = gact(i, p);
				c.fillStyle = B[p];
				c.shadowColor = "black";
				c.font = "12px Verdana";
				c.fillText("" + m[p], 2, a[0] + 32);
				c.shadowColor = B[p];
				var f = ((i - d) * r) - (r / 2);
				var g = gact(i - 1, p);
				if (i && e != g) {
					if (!g) {
						c.fillRect(f, 20 + (a[1] - 2), r / 2, 2);
						c.fillRect(f + (r / 2), 20 + a[0], 2, a[1] - a[0]);
						c.fillRect(f + (r / 2), 20 + a[0], r / 2, 2)
					} else {
						c.fillRect(f, 20 + a[0], r / 2, 2);
						c.fillRect(f + (r / 2), 20 + a[0], 2, a[1] - a[0]);
						c.fillRect(f + (r / 2), 20 + (a[1] - 2), r / 2, 2)
					}
				} else if (e) {
					c.fillRect(f, 20 + a[0], r, 2)
				} else {
					c.fillRect(f, 20 + (a[1] - 2), r, 2)
				}
			}
		}
	};
	return g
}

