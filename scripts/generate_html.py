#!/usr/bin/env python3

import sys

project_name = sys.argv[1]
file_path = sys.argv[2]

f = open(file_path, "w+")

body = "<!doctype html>\n" \
"<html>\n" \
"  <body>\n" \
"    <canvas class=\"emscripten\" id=\"canvas\" oncontextmenu=\"event.preventDefault()\" tabindex=-1></canvas>\n" \
"    <script type='text/javascript'>\n" \
"      var Module = {\n" \
"        canvas: (function() {\n" \
"          var canvas = document.getElementById('canvas');\n" \
"          canvas.addEventListener(\"webglcontextlost\", function(e) {\n" \
"            alert('WebGL context lost. You will need to reload the page.');\n" \
"            e.preventDefault();\n" \
"          }, false);\n" \
"          return canvas;\n" \
"        })(),\n" \
"      };\n" \
"    </script>\n" \
"    <script async type=\"text/javascript\" src=\"" + project_name + ".js\"></script>\n" \
"  </body>\n" \
"</html>\n"

f.write(body)
f.close()
