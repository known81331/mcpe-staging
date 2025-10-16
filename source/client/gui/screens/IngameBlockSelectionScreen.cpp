/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "IngameBlockSelectionScreen.hpp"
#include "PaneCraftingScreen.hpp"
#include "PauseScreen.hpp"
#include "ChatScreen.hpp"
#include "client/app/Minecraft.hpp"
#include "client/renderer/entity/ItemRenderer.hpp"

std::string g_sNotAvailableInDemoVersion = "Not available in the demo version";



const int slotsize = 28;

namespace TouchInventory {
	int wndx = 32, wndy = 2;
	int width = 255, height = 144;

	void drawBG(Screen *screen) {
		int m_width = width;
		int m_height = height;

		Textures* pTexs = screen->m_pMinecraft->m_pTextures;

		pTexs->loadAndBindTexture("gui/spritesheet.png");

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		
		const int texSize = 8;
			
		screen->blit(wndx, wndy, 				  				  8,  8, m_width, m_height, 16,  16);
		screen->blit(wndx, wndy, 				  				  15, 0, m_width, texSize, 1,16);
		screen->blit(wndx, wndy+m_height-texSize, 				  15, 16, m_width, texSize, 1,16);
		screen->blit(wndx, wndy, 				  				  0,  8, texSize, m_height, 16,  16);
		screen->blit(wndx+m_width-texSize, wndy,  				  16, 8, texSize, m_height, 16,  16);
		screen->blit(wndx, wndy, 				  				  0,  0, texSize, texSize, 16,16);
		screen->blit(wndx+m_width-texSize, wndy,  				  16, 0, texSize, texSize, 16,  16);
		screen->blit(wndx, wndy+m_height-texSize, 				  0,  16, texSize, texSize, 16,  16);
		screen->blit(wndx+m_width-texSize, wndy+m_height-texSize, 16, 16, texSize, texSize, 16,  16);
	}


}


IngameBlockSelectionScreen::IngameBlockSelectionScreen() :
	m_btnPause(0, "Pause"),
	m_btnChat(3, "Chat"), // Temp chat button,
	m_btnArmor(1, "Armor"),
	m_btnCrafting(2, "Craft")
{
	m_selectedSlot = 0;
}

Inventory* IngameBlockSelectionScreen::getInventory()
{
	return m_pMinecraft->m_pLocalPlayer->m_pInventory;
}

int IngameBlockSelectionScreen::getBottomY()
{
	// -1 for some reason, -2 to make it align between top of screen and top of hotbar instead
	return (m_height - slotsize * (getSlotsHeight() - 2)) / 2;
}

int IngameBlockSelectionScreen::getSelectedSlot(int x, int y)
{
	int slotsHeight = getSlotsHeight();
	int top = slotsHeight * 10;
	int left = 2;

	if (y < slotsize)
		return -1;
	if (x < left)
		return -1;

	int idx = (x - left) / slotsize;
	int idy = (float)(y)/top * slotsHeight / 2 -1;

	return idx + ((m_width/slotsize) ) * idy;
}

int IngameBlockSelectionScreen::getSlotPosX(int x)
{
	return slotsize * x+2;
}

int IngameBlockSelectionScreen::getSlotPosY(int y)
{
	return slotsize * y + slotsize;
}

int IngameBlockSelectionScreen::getSlotsHeight()
{
	return getInventory()->getNumSlots() / (m_width/slotsize) + 1;
}


bool IngameBlockSelectionScreen::isAllowed(int slot)
{
	return slot >= 0 && slot < getInventory()->getNumSlots();
}

void IngameBlockSelectionScreen::init()
{
	
	m_btnCrafting.m_width = 40;
	m_btnCrafting.m_xPos = 0; //m_pMinecraft->width-40;
	m_btnCrafting.m_yPos = 0;

	m_btnArmor.m_width = 40;
	m_btnArmor.m_xPos = 40; //m_pMinecraft->width-80;
	m_btnArmor.m_yPos = 0;

	m_btnPause.m_width = m_btnPause.m_height = 19;
	m_btnPause.m_xPos = m_width-19;
	m_btnPause.m_yPos = 0;
#if MC_PLATFORM_IOS
	if (m_pMinecraft->isTouchscreen())
		m_buttons.push_back(&m_btnPause);
#endif
	
	m_btnChat.m_width = 40;
	m_btnChat.m_xPos = m_width - m_btnChat.m_width-19-19; // Right edge
    m_btnChat.m_yPos = 0;
	if (m_pMinecraft->isTouchscreen())
		m_buttons.push_back(&m_btnChat);

	
	m_buttons.push_back(&m_btnCrafting);
	m_buttons.push_back(&m_btnArmor);

	Inventory* pInv = getInventory();

	int nItems = pInv->getNumItems();

	for (int i = 0; i < nItems; i++)
	{
		ItemInstance* item = pInv->getItem(i);
		if (item && item->m_itemID == pInv->getSelectedItemId())
		{
			m_selectedSlot = i;
			break;
		}
	}

	if (!isAllowed(m_selectedSlot))
		m_selectedSlot = 0;
}

void IngameBlockSelectionScreen::renderSlot(int index, int x, int y, float f)
{
	ItemInstance* pItem = getInventory()->getItem(index);
	if (ItemInstance::isNull(pItem))
		return;

	ItemRenderer::renderGuiItem(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, pItem, x, y, true);
	ItemRenderer::renderGuiItemOverlay(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, pItem, x, y);
}

void IngameBlockSelectionScreen::renderSlots()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMinecraft->m_pTextures->loadAndBindTexture("gui/gui.png");

	if (m_selectedSlot >= 0)
		blit(slotsize * (m_selectedSlot % (m_width/slotsize)),  slotsize * (m_selectedSlot / (m_width/slotsize)) + slotsize, 0, slotsize, slotsize, slotsize, 0, 0);

	for (int y = 0, index = 0; y < getSlotsHeight(); y++)
	{
		int posY = getSlotPosY(y) + 4;

		for (int x = 0; x < m_width/slotsize; x++)
		{
			int posX = getSlotPosX(x) + 34;
			renderSlot(index++, posX, posY, 0.0f);
		}
	}
}

void IngameBlockSelectionScreen::renderDemoOverlay()
{
	fill(getSlotPosX(0) - 3, getSlotPosY(1) - 3, getSlotPosX(9), getSlotPosY(-1), 0xA0000000);
	
	int x = (getSlotPosX(4) + getSlotPosX(5)) / 2;
	int y = (getSlotPosY(0) + getSlotPosY(1)) / 2 + 5;

	drawCenteredString(m_pMinecraft->m_pFont, g_sNotAvailableInDemoVersion, x, y, 0xFFFFFFFF);
}

void IngameBlockSelectionScreen::render(int x, int y, float f)
{
	Screen::render(x, y, f);
	glDisable(GL_DEPTH_TEST);

	fill(0, 0, m_width, m_height, 0x80000000);


	const int invHeight = 28;

	TouchInventory::wndx = 2;
	TouchInventory::width = invHeight+4;
	TouchInventory::height = invHeight;
	TouchInventory::drawBG(this);

	{
		ItemInstance item( Tile::redBrick->m_ID, 0, 0 );

		TouchInventory::wndx = 2;
		TouchInventory::wndy = m_height-24-invHeight;
		TouchInventory::width = invHeight+4;
		TouchInventory::height = invHeight;
		TouchInventory::drawBG(this);
		ItemRenderer::renderGuiItem(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, &item, TouchInventory::wndx + 7, TouchInventory::wndy + 6, true);
	}

	{
		ItemInstance item( Tile::bookshelf->m_ID, 0, 0 );

		TouchInventory::wndx = 2;
		TouchInventory::wndy = m_height-24-invHeight*2-2;
		TouchInventory::width = invHeight+4;
		TouchInventory::height = invHeight;
		TouchInventory::drawBG(this);
		ItemRenderer::renderGuiItem(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, &item, TouchInventory::wndx + 7, TouchInventory::wndy + 6, true);
	}

	{
		ItemInstance item( Item::sword_iron->m_itemID, 0, 0 );

		TouchInventory::wndx = 2;
		TouchInventory::wndy = m_height-24-invHeight*3-4;
		TouchInventory::width = invHeight+4;
		TouchInventory::height = invHeight;
		TouchInventory::drawBG(this);
		ItemRenderer::renderGuiItem(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, &item, TouchInventory::wndx + 7, TouchInventory::wndy + 6, true);
	}

	{
		ItemInstance item( Item::seeds->m_itemID, 0, 0 );

		TouchInventory::wndx = 2;
		TouchInventory::wndy = m_height-24-invHeight*4-6;
		TouchInventory::width = invHeight+4;
		TouchInventory::height = invHeight;
		TouchInventory::drawBG(this);
		ItemRenderer::renderGuiItem(m_pMinecraft->m_pFont, m_pMinecraft->m_pTextures, &item, TouchInventory::wndx + 7, TouchInventory::wndy + 6, true);
	}


	TouchInventory::wndx = invHeight;
	TouchInventory::wndy = 2;
	TouchInventory::width = m_width - invHeight-2;
	TouchInventory::height = m_height - 24;
	TouchInventory::drawBG(this);


	
	glEnable(GL_BLEND);
	renderSlots();

#ifdef DEMO
	renderDemoOverlay();
#endif

	glEnable(GL_DEPTH_TEST);
}

void IngameBlockSelectionScreen::buttonClicked(Button* pButton)
{
	if (pButton->m_buttonId == m_btnPause.m_buttonId)
		m_pMinecraft->setScreen(new PauseScreen);

	if (pButton->m_buttonId == m_btnChat.m_buttonId)
        m_pMinecraft->setScreen(new ChatScreen(true));


	if (pButton->m_buttonId == m_btnCrafting.m_buttonId)
		m_pMinecraft->setScreen(new PaneCraftingScreen);
}

void IngameBlockSelectionScreen::mouseClicked(int x, int y, int type)
{
	Screen::mouseClicked(x, y, type);
	
	// not a left click
	if (type != 1)
		return;

	int slot = getSelectedSlot(x, y);
	if (isAllowed(slot))
		m_selectedSlot = slot;
}

void IngameBlockSelectionScreen::mouseReleased(int x, int y, int type)
{
	Screen::mouseReleased(x, y, type);
	
	// not a left click
	if (type != 1)
		return;

	int slot = getSelectedSlot(x, y);
	if (isAllowed(slot) && slot == m_selectedSlot)
		selectSlotAndClose();
}

void IngameBlockSelectionScreen::removed()
{
	m_pMinecraft->m_gui.inventoryUpdated();
}

void IngameBlockSelectionScreen::selectSlotAndClose()
{
	Inventory* pInv = getInventory();
	
	pInv->selectItem(m_selectedSlot, m_pMinecraft->m_gui.getNumUsableSlots());

	m_pMinecraft->m_pSoundEngine->playUI("random.pop2");
	//m_pMinecraft->setScreen(nullptr);
}
