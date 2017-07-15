uniform sampler2D texture;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;
uniform vec3 color4;
uniform vec3 color5;
uniform vec3 color6;
uniform vec3 color7;
uniform vec3 replace1;
uniform vec3 replace2;
uniform vec3 replace3;
uniform vec3 replace4;
uniform vec3 replace5;
uniform vec3 replace6;
uniform vec3 replace7;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec3 eps = vec3(0.009, 0.009, 0.009);

	if( all( greaterThanEqual(pixel, vec4(color1 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color1 + eps, 1.0)) ) )
	   pixel = vec4(replace1, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color2 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color2 + eps, 1.0)) ) )
	   pixel = vec4(replace2, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color3 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color3 + eps, 1.0)) ) )
	   pixel = vec4(replace3, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color4 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color4 + eps, 1.0)) ) )
	   pixel = vec4(replace4, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color5 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color5 + eps, 1.0)) ) )
	   pixel = vec4(replace5, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color6 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color6 + eps, 1.0)) ) )
	   pixel = vec4(replace6, 1.0);

	if( all( greaterThanEqual(pixel, vec4(color7 - eps, 1.0)) ) && all( lessThanEqual(pixel, vec4(color7 + eps, 1.0)) ) )
	   pixel = vec4(replace7, 1.0);

	gl_FragColor = pixel;
}