#include "tutorial_qdmi/device.h"
#include <string>    // For std::string
#include <cstring>   // For std::memcpy
#include <stdexcept> // For std::bad_alloc

enum class SESSION_STATUS { ALLOCATED, INITIALIZED };

struct tutorial_QDMI_Device_Session_impl_d {
  std::string token;
  SESSION_STATUS status = SESSION_STATUS::ALLOCATED;
};

struct tutorial_QDMI_Device_Job_impl_d {
  std::string program;
  QDMI_Job_Status status = QDMI_JOB_STATUS_CREATED;
};

const std::string DEVICE_NAME = "MyTutorialDevice";
const size_t QUBIT_COUNT = 1;

int tutorial_QDMI_device_initialize() {
  // Global startup logic (e.g., hardware connection) goes here
  return QDMI_SUCCESS;
}

int tutorial_QDMI_device_finalize() {
  // Global cleanup logic goes here
  return QDMI_SUCCESS;
}

int tutorial_QDMI_device_session_alloc(tutorial_QDMI_Device_Session *session) {
  if (session == nullptr) return QDMI_ERROR_INVALIDARGUMENT;

  try {
    *session = new tutorial_QDMI_Device_Session_impl_d();
    return QDMI_SUCCESS;
  } catch (const std::bad_alloc&) {
    return QDMI_ERROR_OUTOFMEM;
  }
}

int tutorial_QDMI_device_session_set_parameter(tutorial_QDMI_Device_Session session,
                                            QDMI_Device_Session_Parameter param,
                                            const size_t size, const void *value) {
  if (session == nullptr) return QDMI_ERROR_INVALIDARGUMENT;

  // We only support the TOKEN parameter for this tutorial
  if (param == QDMI_DEVICE_SESSION_PARAMETER_TOKEN && value != nullptr) {
    session->token = std::string(static_cast<const char*>(value), size);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
}

int tutorial_QDMI_device_session_init(tutorial_QDMI_Device_Session session) {
  if (session == nullptr) return QDMI_ERROR_INVALIDARGUMENT;

  // Note: Requiring a TOKEN is a design choice for this tutorial implementation,
  // as QDMI remains flexible about how hardware providers handle authentication.
  if (session->token.empty()) return QDMI_ERROR_PERMISSIONDENIED;

  session->status = SESSION_STATUS::INITIALIZED;
  return QDMI_SUCCESS;
}

void tutorial_QDMI_device_session_free(tutorial_QDMI_Device_Session session) {
  if (session != nullptr) delete session;
}

int tutorial_QDMI_device_session_query_device_property(
    tutorial_QDMI_Device_Session session, const QDMI_Device_Property prop,
    const size_t size, void *value, size_t *size_ret) {

  if (session == nullptr) return QDMI_ERROR_INVALIDARGUMENT;
  if (session->status != SESSION_STATUS::INITIALIZED) return QDMI_ERROR_BADSTATE;

  switch (prop) {
    case QDMI_DEVICE_PROPERTY_NAME: {
      size_t name_size = DEVICE_NAME.size() + 1;
      if (size_ret) *size_ret = name_size;
      if (value == nullptr) return QDMI_SUCCESS; // Step 1: size request

      if (size < name_size) return QDMI_ERROR_INVALIDARGUMENT;
      std::memcpy(value, DEVICE_NAME.c_str(), name_size);
      return QDMI_SUCCESS;
    }
    case QDMI_DEVICE_PROPERTY_SITES: {
      if (size_ret) *size_ret = sizeof(size_t);
      if (value == nullptr) return QDMI_SUCCESS;

      *static_cast<size_t*>(value) = QUBIT_COUNT;
      return QDMI_SUCCESS;
    }
    default: return QDMI_ERROR_NOTSUPPORTED;
  }
}

int tutorial_QDMI_device_session_query_site_property(tutorial_QDMI_Device_Session session,
                                               tutorial_QDMI_Site site,
                                               const QDMI_Site_Property prop,
                                               const size_t size, void *value,
                                               size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int tutorial_QDMI_device_session_query_operation_property(
    tutorial_QDMI_Device_Session session, tutorial_QDMI_Operation operation,
    const size_t num_sites, const tutorial_QDMI_Site *sites, const size_t num_params,
    const double *params, const QDMI_Operation_Property prop, const size_t size,
    void *value, size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int tutorial_QDMI_device_session_create_device_job(tutorial_QDMI_Device_Session session,
                                                tutorial_QDMI_Device_Job *job) {
  if (session == nullptr || job == nullptr) return QDMI_ERROR_INVALIDARGUMENT;
  try {
    *job = new tutorial_QDMI_Device_Job_impl_d();
    return QDMI_SUCCESS;
  } catch (const std::bad_alloc&) {
    return QDMI_ERROR_OUTOFMEM;
  }
}

int tutorial_QDMI_device_job_set_parameter(tutorial_QDMI_Device_Job job,
                                        const QDMI_Device_Job_Parameter param,
                                        const size_t size, const void *value) {
  if (job == nullptr || value == nullptr) return QDMI_ERROR_INVALIDARGUMENT;

  if (param == QDMI_DEVICE_JOB_PARAMETER_PROGRAM) {
    job->program = std::string(static_cast<const char*>(value), size);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
}

int tutorial_QDMI_device_job_query_property(tutorial_QDMI_Device_Job job,
                                      const QDMI_Device_Job_Property prop,
                                      const size_t size, void *value,
                                      size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int tutorial_QDMI_device_job_submit(tutorial_QDMI_Device_Job job) {
  if (job == nullptr) return QDMI_ERROR_INVALIDARGUMENT;
  if (job->program.empty()) return QDMI_ERROR_BADSTATE;

  // Real hardware implementations often use asynchronous execution with
  // states like QUEUED or RUNNING. Here, we simulate immediate completion.
  job->status = QDMI_JOB_STATUS_DONE;
  return QDMI_SUCCESS;
}

int tutorial_QDMI_device_job_cancel(tutorial_QDMI_Device_Job job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int tutorial_QDMI_device_job_check(tutorial_QDMI_Device_Job job, QDMI_Job_Status *status) {
  if (job == nullptr || status == nullptr) return QDMI_ERROR_INVALIDARGUMENT;
  *status = job->status;
  return QDMI_SUCCESS;
}

int tutorial_QDMI_device_job_wait(tutorial_QDMI_Device_Job job, const size_t timeout) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int tutorial_QDMI_device_job_get_results(tutorial_QDMI_Device_Job job,
                                      QDMI_Job_Result result, const size_t size,
                                      void *data, size_t *size_ret) {
  if (job == nullptr || job->status != QDMI_JOB_STATUS_DONE) return QDMI_ERROR_BADSTATE;

  if (result == QDMI_JOB_RESULT_PROBABILITIES_DENSE) {
    const double probs[] = {0.5, 0.5};
    size_t res_size = sizeof(probs);

    if (size_ret) *size_ret = res_size;
    if (data == nullptr) return QDMI_SUCCESS;

    if (size < res_size) return QDMI_ERROR_INVALIDARGUMENT;
    std::memcpy(data, probs, res_size);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
}

void tutorial_QDMI_device_job_free(tutorial_QDMI_Device_Job job) {
  if (job != nullptr) delete job;
}
