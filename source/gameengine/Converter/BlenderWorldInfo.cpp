/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can [0]istribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file gameengine/Converter/BlenderWorldInfo.cpp
 *  \ingroup bgeconv
 */


#include <stdio.h>  // printf()

#include "BlenderWorldInfo.h"

/* This little block needed for linking to Blender... */
#ifdef WIN32
#include "BLI_winstuff.h"
#endif

/* This list includes only data type definitions */
#include "DNA_object_types.h"
#include "DNA_material_types.h"
#include "DNA_image_types.h"
#include "DNA_lamp_types.h"
#include "DNA_group_types.h"
#include "DNA_scene_types.h"
#include "DNA_camera_types.h"
#include "DNA_property_types.h"
#include "DNA_text_types.h"
#include "DNA_sensor_types.h"
#include "DNA_controller_types.h"
#include "DNA_actuator_types.h"
#include "DNA_mesh_types.h"
#include "DNA_meshdata_types.h"
#include "DNA_view3d_types.h"
#include "DNA_world_types.h"
#include "DNA_screen_types.h"

#include "BLI_math.h"

#include "BKE_global.h"
#include "BKE_scene.h"
/* end of blender include block */


BlenderWorldInfo::BlenderWorldInfo(struct Scene *blenderscene, struct World *blenderworld)
{
	if (blenderworld) {
		m_hasworld = true;
		m_hasmist = ((blenderworld->mode) & WO_MIST ? true : false);
		m_misttype = blenderworld->mistype;
		m_miststart = blenderworld->miststa;
		m_mistdistance = blenderworld->mistdist;
		m_mistintensity = blenderworld->misi;
		copy_v3_v3(m_mistcolor, &blenderworld->horr);
		copy_v3_v3(m_backgroundcolor, &blenderworld->horr);
		copy_v3_v3(m_ambientcolor, &blenderworld->ambr);

		if (BKE_scene_check_color_management_enabled(blenderscene)) {
			linearrgb_to_srgb_v3_v3(m_mistcolor, m_mistcolor);
			linearrgb_to_srgb_v3_v3(m_backgroundcolor, m_backgroundcolor);
			linearrgb_to_srgb_v3_v3(m_ambientcolor, m_ambientcolor);
		}
	}
	else {
		m_hasworld = false;
	}
}

BlenderWorldInfo::~BlenderWorldInfo()
{
}

bool BlenderWorldInfo::hasWorld()
{
	return m_hasworld;
}

bool BlenderWorldInfo::hasMist()
{
	return m_hasmist;
}

float BlenderWorldInfo::getBackColorRed()
{
	return m_backgroundcolor[0];
}

float BlenderWorldInfo::getBackColorGreen()
{
	return m_backgroundcolor[1];
}

float BlenderWorldInfo::getBackColorBlue()
{
	return m_backgroundcolor[2];
}

float BlenderWorldInfo::getAmbientColorRed()
{
	return m_ambientcolor[0];
}

float BlenderWorldInfo::getAmbientColorGreen()
{
	return m_ambientcolor[1];
}

float BlenderWorldInfo::getAmbientColorBlue()
{
	return m_ambientcolor[2];
}

short BlenderWorldInfo::getMistType()
{
	return m_misttype;
}

float BlenderWorldInfo::getMistStart()
{
	return m_miststart;
}

float BlenderWorldInfo::getMistDistance()
{
	return m_mistdistance;
}

float BlenderWorldInfo::getMistIntensity()
{
	return m_mistintensity;
}

float BlenderWorldInfo::getMistColorRed()
{
	return m_mistcolor[0];
}

float BlenderWorldInfo::getMistColorGreen()
{
	return m_mistcolor[1];
}

float BlenderWorldInfo::getMistColorBlue()
{
	return m_mistcolor[2];
}

void BlenderWorldInfo::setBackColor(float r, float g, float b)
{
	m_backgroundcolor[0] = r;
	m_backgroundcolor[1] = g;
	m_backgroundcolor[2] = b;
}

void BlenderWorldInfo::setMistType(short type)
{
	m_misttype = type;
}

void BlenderWorldInfo::setUseMist(bool enable)
{
	m_hasmist = enable;
}

void BlenderWorldInfo::setMistStart(float d)
{
	m_miststart = d;
}

void BlenderWorldInfo::setMistDistance(float d)
{
	m_mistdistance = d;
}

void BlenderWorldInfo::setMistIntensity(float intensity)
{
	m_mistintensity = intensity;
}
void BlenderWorldInfo::setMistColor(float r, float g, float b)
{
	m_mistcolor[0] = r;
	m_mistcolor[1] = g;
	m_mistcolor[2] = b;
}

void BlenderWorldInfo::setAmbientColor(float r, float g, float b)
{
	m_ambientcolor[0] = r;
	m_ambientcolor[1] = g;
	m_ambientcolor[2] = b;
}
