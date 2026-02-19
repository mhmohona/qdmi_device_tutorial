# tutorial QDMI Device

This project serves as a **reference implementation** of a QDMI (Quantum Device Management Interface) device. It was created as the hands-on component of the [QDMI Tutorial](https://github.com/mhmohona/QDMI/blob/device-implementation/docs/tutorial.md), providing a concrete example of how to build, configure, and test a QDMI-compliant hardware abstraction layer.

## Purpose

The main goal of this project is to demonstrate:
1.  **Lifecycle Management**: Implementing global initialization and finalization.
2.  **Session Orchestration**: Managing opaque handles for device sessions and authentication.
3.  **Property Querying**: Implementing the two-step pattern for variable-sized hardware metadata.
4.  **Job Execution**: Simulating the submission, monitoring, and result retrieval of quantum workloads.

## Getting Started

This implementation was built following the step-by-step instructions in [docs/tutorial.md](https://github.com/mhmohona/QDMI/blob/device-implementation/docs/tutorial.md). If you are looking to learn how to implement your own QDMI device, we recommend following that guide from the beginning.

### Build and Test

To verify this implementation, you can run the following commands:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target tutorial-qdmi-device-test
ctest --test-dir build -C Release --output-on-failure
```
