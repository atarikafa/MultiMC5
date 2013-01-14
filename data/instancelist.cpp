/* Copyright 2013 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "instancelist.h"

#include <QDir>
#include <QDirIterator>

#include "stdinstance.h"

#include "../util/pathutils.h"

InstanceList::InstanceList() :
	QList()
{
	
}

void InstanceList::addInstance(InstanceBase *inst)
{
	append(inst);
}

void InstanceList::loadInstances(QString dir)
{
	qDebug("Loading instances");
	QDir instDir(dir);
	QDirIterator iter(instDir);
	
	while (iter.hasNext())
	{
		QString subDir = iter.next();
		if (QFileInfo(PathCombine(subDir, "instance.cfg")).exists())
		{
			// TODO Differentiate between different instance types.
			InstanceBase* inst = new StdInstance(subDir);
			addInstance(inst);
		}
	}
}
