/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <string>
#include <unistd.h>
#include "hdf_uhdf_test.h"
#include "hdf_io_service_if.h"

using namespace testing::ext;

#define HDF_TEST_NAME "/dev/hdf_test"

enum HdfLiteUsbTestCmd {
    USB_WRITE_TEST = 0,
    USB_HOSTSDK_INIT_001_TEST,
    USB_HOSTSDK_EXIT_001_TEST,
    USB_HOSTSDK_INIT_002_TEST,
    USB_HOSTSDK_EXIT_002_TEST,
    USB_HOSTSDK_INIT_003_TEST,
    USB_HOSTSDK_INIT_004_TEST,
    USB_HOSTSDK_INIT_005_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_001_TEST,
    USB_HOSTSDK_RELEASE_INTERFACE_001_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_002_TEST,
    USB_HOSTSDK_RELEASE_INTERFACE_002_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_003_TEST,
    USB_HOSTSDK_RELEASE_INTERFACE_003_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_004_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_005_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_006_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_001_TEST,
    USB_HOSTSDK_CLOSE_INTERFACE_001_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_002_TEST,
    USB_HOSTSDK_CLOSE_INTERFACE_002_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_003_TEST,
    USB_HOSTSDK_CLOSE_INTERFACE_003_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_004_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_005_TEST,
    USB_HOSTSDK_CLOSE_INTERFACE_005_TEST,
    USB_HOSTSDK_OPEN_INTERFACE_006_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_001_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_002_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_003_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_004_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_005_TEST,
    USB_HOSTSDK_SELECT_INTERFACE_006_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_007_TEST,
    USB_HOSTSDK_CLAIM_INTERFACE_008_TEST,
    USB_HOSTSDK_GET_PIPE_001_TEST,
    USB_HOSTSDK_GET_PIPE_002_TEST,
    USB_HOSTSDK_GET_PIPE_003_TEST,
    USB_HOSTSDK_GET_PIPE_004_TEST,
    USB_HOSTSDK_GET_PIPE_005_TEST,
    USB_HOSTSDK_GET_PIPE_006_TEST,
    USB_HOSTSDK_GET_PIPE_007_TEST,
    USB_HOSTSDK_GET_PIPE_008_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_001_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_002_TEST,
    USB_HOSTSDK_FREE_REQUEST_001_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_003_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_004_TEST,
    USB_HOSTSDK_FREE_REQUEST_002_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_005_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_006_TEST,
    USB_HOSTSDK_FREE_REQUEST_003_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_007_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_008_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_010_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_011_TEST,
    USB_HOSTSDK_FREE_REQUEST_006_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_001_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_002_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_003_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_004_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_005_TEST,
    USB_HOSTSDK_FILL_ISO_REQUEST_006_TEST,
    USB_HOSTSDK_FREE_REQUEST_004_TEST,
    USB_HOSTSDK_ALLOC_REQUEST_009_TEST,
    USB_HOSTSDK_FILL_REQUEST_001_TEST,
    USB_HOSTSDK_FILL_REQUEST_002_TEST,
    USB_HOSTSDK_FILL_REQUEST_003_TEST,
    USB_HOSTSDK_FILL_REQUEST_004_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_SYNC_001_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_SYNC_002_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_SYNC_003_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_SYNC_004_TEST,
    USB_HOSTSDK_FILL_REQUEST_005_TEST,
    USB_HOSTSDK_FILL_REQUEST_006_TEST,
    USB_HOSTSDK_FILL_REQUEST_007_TEST,
    USB_HOSTSDK_FILL_REQUEST_008_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_ASYNC_001_TEST,
    USB_HOSTSDK_SUBMIT_CANCEL_REQUEST_001_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_ASYNC_002_TEST,
    USB_HOSTSDK_SUBMIT_CANCEL_REQUEST_002_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_ASYNC_003_TEST,
    USB_HOSTSDK_SUBMIT_CANCEL_REQUEST_003_TEST,
    USB_HOSTSDK_SUBMIT_REQUEST_ASYNC_004_TEST,
    USB_HOSTSDK_SUBMIT_CANCEL_REQUEST_004_TEST,
    USB_HOSTSDK_CLEAR_INTERFACE_HALT_002_TEST,
    USB_HOSTSDK_CLEAR_INTERFACE_HALT_003_TEST,
    USB_HOSTSDK_CLEAR_INTERFACE_HALT_004_TEST,
    USB_HOSTSDK_REMOVE_INTERFACE_001_TEST,
    USB_HOSTSDK_ADD_INTERFACE_001_TEST,
    USB_HOSTSDK_REMOVE_INTERFACE_002_TEST,
    USB_HOSTSDK_ADD_INTERFACE_002_TEST,
    USB_HOSTSDK_REMOVE_INTERFACE_003_TEST,
    USB_HOSTSDK_ADD_INTERFACE_003_TEST,
    USB_HOSTSDK_CLOSE_INTERFACE_006_TEST,
};

class hdf_usb_test1 : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void hdf_usb_test1::SetUpTestCase()
{
    HdfTestOpenService();
}

void hdf_usb_test1::TearDownTestCase()
{
    HdfTestCloseService();
}

/**
 * @tc.number    : CheckHostSdkIfInit001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfInit001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_INIT_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfClaimInterface006
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfClaimInterface006, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLAIM_INTERFACE_006_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfOpenInterface006
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfOpenInterface006, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_OPEN_INTERFACE_006_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfSelectInterfaceSetting006
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfSelectInterfaceSetting006, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_SELECT_INTERFACE_006_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}


/**
 * @tc.number    : CheckHostSdkIfClaimInterface007
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfClaimInterface007, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLAIM_INTERFACE_007_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfClaimInterface008
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfClaimInterface008, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLAIM_INTERFACE_008_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfGetPipe002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfGetPipe002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_GET_PIPE_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfGetPipe004
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfGetPipe004, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_GET_PIPE_004_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfGetPipe006
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfGetPipe006, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_GET_PIPE_006_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfGetPipe008
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfGetPipe008, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_GET_PIPE_008_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfAllocRequest009
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfAllocRequest009, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_ALLOC_REQUEST_009_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFillRequest001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFillRequest001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FILL_REQUEST_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFillRequest002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFillRequest002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FILL_REQUEST_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFillRequest003
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFillRequest003, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FILL_REQUEST_003_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFillRequest004
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFillRequest004, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FILL_REQUEST_004_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfSubmitRequestSync003
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfSubmitRequestSync003, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_SUBMIT_REQUEST_SYNC_003_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfSubmitRequestSync002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfSubmitRequestSync002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_SUBMIT_REQUEST_SYNC_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfSubmitRequestSync001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfSubmitRequestSync001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_SUBMIT_REQUEST_SYNC_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfSubmitRequestSync004
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfSubmitRequestSync004, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_SUBMIT_REQUEST_SYNC_004_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFreeRequest001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFreeRequest001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FREE_REQUEST_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFreeRequest002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFreeRequest002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FREE_REQUEST_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFreeRequest003
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFreeRequest003, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FREE_REQUEST_003_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfFreeRequest004
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfFreeRequest004, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_FREE_REQUEST_004_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfCloseInterface001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfCloseInterface001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLOSE_INTERFACE_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfCloseInterface002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfCloseInterface002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLOSE_INTERFACE_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfCloseInterface003
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfCloseInterface003, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_CLOSE_INTERFACE_003_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfReleaseInterface001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfReleaseInterface001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_RELEASE_INTERFACE_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfReleaseInterface002
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfReleaseInterface002, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_RELEASE_INTERFACE_002_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfReleaseInterface003
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfReleaseInterface003, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_RELEASE_INTERFACE_003_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}

/**
 * @tc.number    : CheckHostSdkIfExit001
 * @tc.name      :
 * @tc.type      : PERF
 * @tc.level     : Level 1
 */
HWTEST_F(hdf_usb_test1, CheckHostSdkIfExit001, TestSize.Level1)
{
    struct HdfTestMsg msg = {TEST_USB_HOST_TYPE, USB_HOSTSDK_EXIT_001_TEST, -1};
    EXPECT_EQ(0, HdfTestSendMsgToService(&msg));
}
