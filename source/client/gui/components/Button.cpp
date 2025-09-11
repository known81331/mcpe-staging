/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "Button.hpp"

void Button::_init()
{
	m_width = 0;
	m_height = 0;
	m_xPos = 0;
	m_yPos = 0;
	m_text = "";
	m_bEnabled = true;
	m_bVisible = true;
	field_36 = false;

#ifndef ORIGINAL_CODE
	m_lastX = 0;
	m_lastY = 0;
#endif
}

Button::Button(int buttonId, int xPos, int yPos, int btnWidth, int btnHeight, const std::string& text)
{
	_init();

	m_buttonId = buttonId;
	m_xPos = xPos;
	m_yPos = yPos;
	m_text = text;
	m_width  = btnWidth;
	m_height = btnHeight;
}

Button::Button(int buttonId, int xPos, int yPos, const std::string& text)
{
	_init();

	m_buttonId = buttonId;
	m_xPos = xPos;
	m_yPos = yPos;
	m_text = text;
	m_width  = 200;
	m_height = 24;
}

Button::Button(int buttonId, const std::string& text)
{
	_init();

	m_buttonId = buttonId;
	m_text = text;
	m_width  = 200;
	m_height = 24;
}

bool Button::clicked(Minecraft* pMinecraft, int xPos, int yPos)
{
	if (!m_bEnabled) return false;
	if (xPos < m_xPos) return false;
	if (yPos < m_yPos) return false;
	if (xPos >= m_xPos + m_width) return false;
	if (yPos >= m_yPos + m_height) return false;

	return true;
}

int Button::getYImage(bool bHovered)
{
	if (!m_bEnabled) return 0;
	if (bHovered) return 2;
	return 1;
}

void Button::released(int xPos, int yPos)
{

}

void Button::renderBg(Minecraft*, int, int)
{

}

void Button::render(Minecraft* pMinecraft, int xPos, int yPos)
{

#ifdef ORIGINAL_CODE
	if (!m_bVisible) return;

	if (!pMinecraft->useController())
		field_36 = clicked(pMinecraft, xPos, yPos);

	Font* pFont = pMinecraft->m_pFont;
	Textures* pTexs = pMinecraft->m_pTextures;

	pTexs->loadAndBindTexture("gui/gui.png");

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int iYPos = 20 * getYImage(field_36) + 46;

	blit(m_xPos, m_yPos, 0, iYPos, m_width / 2, m_height, 0, 20);
	blit(m_xPos + m_width / 2, m_yPos, 200 - m_width / 2, iYPos, m_width / 2, m_height, 0, 20);

	renderBg(pMinecraft, xPos, yPos);

	int textColor;
	if (!m_bEnabled)
		textColor = int(0xFFA0A0A0U);
	else if (field_36)
		textColor = int(0xFFFFA0U);
	else
		textColor = int(0xE0E0E0U);

	drawCenteredString(pFont, m_text, m_xPos + m_width / 2, m_yPos + (m_height - 8) / 2, textColor);
#else
if (!m_bVisible) return;

#if !TARGET_OS_IPHONE && !TARGET_OS_ANDROID
if (m_bHoverable)
	field_36 = clicked(pMinecraft, xPos, yPos);
#endif

	Font* pFont = pMinecraft->m_pFont;
	Textures* pTexs = pMinecraft->m_pTextures;

	pTexs->loadAndBindTexture("gui/spritesheet.png");

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int iYPos = 64; //20 * getYImage(field_36) + 46;
    
    if (!field_36) {
        blit(m_xPos, m_yPos, 16, iYPos, 5, 13, 5, 22);
        blit(m_xPos+2, m_yPos, 20, iYPos, m_width-2, 13, 5, 22);
        blit(m_xPos + m_width - 10, m_yPos, 22, iYPos, 10, 13, 10, 22);
        
        iYPos = 68;
        
        blit(m_xPos, m_yPos+6, 16, iYPos, 5, m_height-6, 5, 8);
        blit(m_xPos+2, m_yPos+6, 20, iYPos, m_width-2, m_height-6, 5, 8);
        blit(m_xPos + m_width - 10, m_yPos+6, 22, iYPos, 10, m_height-6, 10, 8);
        
        blit(m_xPos, m_yPos+m_height-10, 16, iYPos, 5, 13, 5, 16);
        blit(m_xPos+2, m_yPos+m_height-10, 20, iYPos, m_width-2, 13, 5, 16);
        blit(m_xPos + m_width - 10, m_yPos+m_height-10, 22, iYPos, 10, 13, 10, 16);
        
    }
    else {
        blit(m_xPos, m_yPos, 0, iYPos, 5, 13, 5, 15);
        blit(m_xPos+2, m_yPos, 2, iYPos, m_width-2, 13, 5, 15);
        blit(m_xPos + m_width - 10, m_yPos, 6, iYPos, 10, 13, 10, 15);
        
        iYPos = 68;
        
        blit(m_xPos, m_yPos+6, 0, iYPos, 5, m_height-10, 5, 6);
        blit(m_xPos+2, m_yPos+6, 2, iYPos, m_width-2, m_height-10, 5, 6);
        blit(m_xPos + m_width - 10, m_yPos+6, 6, iYPos, 10, m_height-10, 10, 6);
        
        blit(m_xPos, m_yPos+m_height-10, 0, iYPos, 5, 10, 5, 10);
        blit(m_xPos+2, m_yPos+m_height-10, 2, iYPos, m_width-2, 10, 5, 10);
        blit(m_xPos + m_width - 10, m_yPos+m_height-10, 6, iYPos, 10, 10, 10, 10);
    }
    
	renderBg(pMinecraft, xPos, yPos);

	int textColor;
	if (!m_bEnabled)
		textColor = int(0xFFA0A0A0U);
	else if (field_36)
		textColor = int(0xFFFFA0U);
	else
		textColor = int(0xE0E0E0U);

	drawCenteredString(pFont, m_text, m_xPos + m_width / 2, m_yPos + (m_height - 8) / 2, textColor);
#endif
}
