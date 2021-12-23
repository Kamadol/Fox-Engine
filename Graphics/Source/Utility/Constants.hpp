#ifndef CONTANTS_HPP
#define CONTANTS_HPP

#include "Vertices\SpriteVertex.hpp"
#include "RenderText.hpp"

//GUI
const float updateTime = 0.2f;

//Font
const unsigned int glyphXCount =  10;
const unsigned int glyphYCount =  10;
const unsigned int asciiFrom   =  32;
const unsigned int asciiTo     = 126;

//TextRenderer
const unsigned int maxGlyphs		=									  256;
const unsigned int glyphsSize		=		   sizeof(TextVertex) * maxGlyphs;
const unsigned int textIndicesCount =							maxGlyphs * 6;
const unsigned int textIndicesSize  = sizeof(unsigned int) * textIndicesCount;

//SpriteRenderer
const unsigned int maxSprites		  =										 10000;
const unsigned int spritesSize		  =		 sizeof(SpriteVertex) * maxSprites * 4;
const unsigned int spriteIndicesCount =								maxSprites * 6;
const unsigned int spriteIndicesSize  =  sizeof(unsigned int) * spriteIndicesCount;

#endif
