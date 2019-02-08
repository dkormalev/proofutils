/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "proofnetwork/mis/data/qmlwrappers/jobqmlwrapper.h"

#include "proofnetwork/mis/data/job.h"
#include "proofnetwork/qmlwrappers/networkdataentityqmlwrapper_p.h"

namespace Proof {
namespace Mis {

class JobQmlWrapperPrivate : public NetworkDataEntityQmlWrapperPrivate
{
    Q_DECLARE_PUBLIC(JobQmlWrapper)
};

JobQmlWrapper::JobQmlWrapper(const JobSP &job, QObject *parent)
    : NetworkDataEntityQmlWrapper(job, *new JobQmlWrapperPrivate, parent)
{
    setupEntity(); // NOLINT
}

JobQmlWrapper::~JobQmlWrapper()
{}

PROOF_NDE_WRAPPER_TOOLS_IMPL(Job)

PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, QString, id)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, Proof::Mis::EntityStatus, status)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, QString, name)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, qlonglong, quantity)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, double, width)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, double, height)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, QString, source)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, int, pageCount)
PROOF_NDE_WRAPPER_PROPERTY_IMPL_R(Job, bool, hasPreview)

WorkflowStatus JobQmlWrapper::workflowStatus(WorkflowAction action, PaperSide paperSide) const
{
    const JobSP job = entity<Job>();
    Q_ASSERT(job);
    return job->workflowStatus(action, paperSide);
}

void JobQmlWrapper::setupEntity(const QSharedPointer<NetworkDataEntity> &old)
{
    JobSP job = entity<Job>();
    Q_ASSERT(job);

    connect(job.data(), &Job::idChanged, this, &JobQmlWrapper::idChanged);
    connect(job.data(), &Job::statusChanged, this, &JobQmlWrapper::statusChanged);
    connect(job.data(), &Job::nameChanged, this, &JobQmlWrapper::nameChanged);
    connect(job.data(), &Job::quantityChanged, this, &JobQmlWrapper::quantityChanged);
    connect(job.data(), &Job::widthChanged, this, &JobQmlWrapper::widthChanged);
    connect(job.data(), &Job::heightChanged, this, &JobQmlWrapper::heightChanged);
    connect(job.data(), &Job::sourceChanged, this, &JobQmlWrapper::sourceChanged);
    connect(job.data(), &Job::pageCountChanged, this, &JobQmlWrapper::pageCountChanged);
    connect(job.data(), &Job::hasPreviewChanged, this, &JobQmlWrapper::hasPreviewChanged);
    connect(job.data(), &Job::workflowChanged, this, &JobQmlWrapper::workflowChanged);

    JobSP oldJob = qSharedPointerCast<Job>(old);
    if (oldJob) {
        if (job->id() != oldJob->id())
            emit idChanged(job->id());
        if (job->status() != oldJob->status())
            emit statusChanged(job->status());
        if (job->name() != oldJob->name())
            emit nameChanged(job->name());
        if (job->quantity() != oldJob->quantity())
            emit quantityChanged(job->quantity());
        if (!qFuzzyCompare(job->width() + 1.0, oldJob->width() + 1.0))
            emit widthChanged(job->width());
        if (!qFuzzyCompare(job->height() + 1.0, oldJob->height() + 1.0))
            emit heightChanged(job->height());
        if (job->source() != oldJob->source())
            emit sourceChanged(job->source());
        if (job->hasPreview() != oldJob->hasPreview())
            emit hasPreviewChanged(job->hasPreview());
    }
    emit workflowChanged();
}

} // namespace Mis
} // namespace Proof
