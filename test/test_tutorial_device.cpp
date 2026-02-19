#include "tutorial_qdmi/device.h"
#include <gtest/gtest.h>

class QDMIBaseTest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_EQ(tutorial_QDMI_device_initialize(), QDMI_SUCCESS)
        << "Checkpoint 0 Failed: Basic device initialization returned an error.";
  }
  void TearDown() override { tutorial_QDMI_device_finalize(); }
};

class QDMISessionTest : public QDMIBaseTest {
protected:
  tutorial_QDMI_Device_Session session = nullptr;
  void SetUp() override {
    QDMIBaseTest::SetUp();
    ASSERT_EQ(tutorial_QDMI_device_session_alloc(&session), QDMI_SUCCESS)
        << "Checkpoint 1 Failed: Could not allocate a session handle.";
    const std::string token = "tutorial_token";
    ASSERT_EQ(tutorial_QDMI_device_session_set_parameter(session, QDMI_DEVICE_SESSION_PARAMETER_TOKEN, token.size(), token.c_str()), QDMI_SUCCESS);
    ASSERT_EQ(tutorial_QDMI_device_session_init(session), QDMI_SUCCESS)
        << "Checkpoint 2 Failed: Session initialization failed.";
  }
  void TearDown() override {
    if (session) tutorial_QDMI_device_session_free(session);
    QDMIBaseTest::TearDown();
  }
};

TEST_F(QDMIBaseTest, Initialization) {
  // Checkpoint 0: Verified by SetUp/TearDown
}

TEST_F(QDMISessionTest, Allocation) {
  // Checkpoints 1 and 2: Verified by SetUp/TearDown
}

TEST_F(QDMISessionTest, QueryProperties) {
  size_t size = 0;
  ASSERT_EQ(tutorial_QDMI_device_session_query_device_property(session, QDMI_DEVICE_PROPERTY_NAME, 0, nullptr, &size), QDMI_SUCCESS)
      << "Checkpoint 3 Failed: Device failed to report name size.";

  std::string value(size, '\0');
  ASSERT_EQ(tutorial_QDMI_device_session_query_device_property(session, QDMI_DEVICE_PROPERTY_NAME, size, value.data(), nullptr), QDMI_SUCCESS);
  EXPECT_STREQ(value.c_str(), "MyTutorialDevice");
}

TEST_F(QDMISessionTest, SubmitAndSimulateJob) {
  tutorial_QDMI_Device_Job job = nullptr;
  ASSERT_EQ(tutorial_QDMI_device_session_create_device_job(session, &job), QDMI_SUCCESS)
      << "Checkpoint 4 Failed: Could not create a device job.";

  const std::string qasm = "OPENQASM 2.0; qreg q[1]; h q[0];";
  ASSERT_EQ(tutorial_QDMI_device_job_set_parameter(job, QDMI_DEVICE_JOB_PARAMETER_PROGRAM, qasm.size(), qasm.c_str()), QDMI_SUCCESS);
  ASSERT_EQ(tutorial_QDMI_device_job_submit(job), QDMI_SUCCESS)
      << "Checkpoint 4 Failed: Job submission failed.";

  QDMI_Job_Status status;
  ASSERT_EQ(tutorial_QDMI_device_job_check(job, &status), QDMI_SUCCESS);
  EXPECT_EQ(status, QDMI_JOB_STATUS_DONE);

  double probs[2];
  ASSERT_EQ(tutorial_QDMI_device_job_get_results(job, QDMI_JOB_RESULT_PROBABILITIES_DENSE, sizeof(probs), probs, nullptr), QDMI_SUCCESS)
      << "Checkpoint 4 Failed: Could not retrieve simulated job results.";

  tutorial_QDMI_device_job_free(job);
}
