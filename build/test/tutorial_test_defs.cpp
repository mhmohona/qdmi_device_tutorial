/** @file
 * @brief This file is for testing whether a device implements all the required
 * functions.
 * @details It calls all the functions in the device interface to ensure that
 * they are implemented. During linking, when a function is not implemented this
 * will raise an error.
 * @note This file is not meant to be ever executed, only linked.
 */

#include "tutorial_qdmi/device.h"

int main() {
  tutorial_QDMI_Device_Session session = nullptr;
  tutorial_QDMI_Device_Job job = nullptr;
  tutorial_QDMI_Site site = nullptr;
  tutorial_QDMI_Operation operation = nullptr;
  tutorial_QDMI_device_initialize();
  tutorial_QDMI_device_finalize();
  tutorial_QDMI_device_session_alloc(&session);
  tutorial_QDMI_device_session_init(session);
  tutorial_QDMI_device_session_free(session);
  tutorial_QDMI_device_session_set_parameter(session, QDMI_DEVICE_SESSION_PARAMETER_MAX, 0, nullptr);
  tutorial_QDMI_device_session_create_device_job(session, &job);
  tutorial_QDMI_device_job_free(job);
  tutorial_QDMI_device_job_set_parameter(job, QDMI_DEVICE_JOB_PARAMETER_MAX, 0, nullptr);
  tutorial_QDMI_device_job_query_property(job, QDMI_DEVICE_JOB_PROPERTY_MAX, 0, nullptr, nullptr);
  tutorial_QDMI_device_job_submit(job);
  tutorial_QDMI_device_job_cancel(job);
  tutorial_QDMI_device_job_check(job, nullptr);
  tutorial_QDMI_device_job_wait(job, 0);
  tutorial_QDMI_device_job_get_results(job, QDMI_JOB_RESULT_MAX, 0, nullptr, nullptr);
  tutorial_QDMI_device_session_query_device_property(session, QDMI_DEVICE_PROPERTY_MAX, 0, nullptr, nullptr);
  tutorial_QDMI_device_session_query_site_property(session, site, QDMI_SITE_PROPERTY_MAX, 0, nullptr, nullptr);
  tutorial_QDMI_device_session_query_operation_property(session, operation, 0, nullptr, 0, nullptr, QDMI_OPERATION_PROPERTY_MAX, 0, nullptr, nullptr);
}
