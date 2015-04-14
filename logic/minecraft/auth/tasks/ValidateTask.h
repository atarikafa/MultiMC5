/* Copyright 2013-2015 MultiMC Contributors
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

/*
 * :FIXME: DEAD CODE, DEAD CODE, DEAD CODE! :FIXME:
 */

#pragma once

#include "YggdrasilTask.h"

/**
 * The validate task takes a MojangAccount and checks to make sure its access token is valid.
 */
class MULTIMC_LOGIC_EXPORT ValidateTask : public YggdrasilTask
{
	Q_OBJECT
public:
	ValidateTask(MojangAuthSessionPtr session, MojangAccount *account, QObject *parent = 0);

protected:
	friend class ValidateTaskTest;
	QJsonObject getRequestContent() const override;
	QString getEndpoint() const override;
	void processResponse(const QJsonObject &responseData) override;
	QString getStateMessage() const override;
};