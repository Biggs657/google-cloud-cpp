// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_TESTING_MOCK_DATA_CLIENT_H_
#define GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_TESTING_MOCK_DATA_CLIENT_H_

#include "bigtable/client/table.h"
#include <gmock/gmock.h>

namespace bigtable {
namespace testing {

class MockDataClient : public bigtable::DataClient {
 public:
  MOCK_CONST_METHOD0(project_id, std::string const&());
  MOCK_CONST_METHOD0(instance_id, std::string const&());
  MOCK_METHOD0(Channel, std::shared_ptr<grpc::Channel>());
  MOCK_METHOD0(reset, void());

  MOCK_METHOD3(
      MutateRow,
      grpc::Status(grpc::ClientContext* context,
                   google::bigtable::v2::MutateRowRequest const& request,
                   google::bigtable::v2::MutateRowResponse* response));
  MOCK_METHOD3(
      CheckAndMutateRow,
      grpc::Status(
          grpc::ClientContext* context,
          google::bigtable::v2::CheckAndMutateRowRequest const& request,
          google::bigtable::v2::CheckAndMutateRowResponse* response));
  MOCK_METHOD3(
      ReadModifyWriteRow,
      grpc::Status(
          grpc::ClientContext* context,
          google::bigtable::v2::ReadModifyWriteRowRequest const& request,
          google::bigtable::v2::ReadModifyWriteRowResponse* response));
  MOCK_METHOD2(
      ReadRows,
      std::unique_ptr<
          grpc::ClientReaderInterface<google::bigtable::v2::ReadRowsResponse>>(
          grpc::ClientContext* context,
          google::bigtable::v2::ReadRowsRequest const& request));
  MOCK_METHOD2(SampleRowKeys,
               std::unique_ptr<grpc::ClientReaderInterface<
                   google::bigtable::v2::SampleRowKeysResponse>>(
                   grpc::ClientContext* context,
                   google::bigtable::v2::SampleRowKeysRequest const& request));
  MOCK_METHOD2(MutateRows,
               std::unique_ptr<grpc::ClientReaderInterface<
                   google::bigtable::v2::MutateRowsResponse>>(
                   grpc::ClientContext* context,
                   google::bigtable::v2::MutateRowsRequest const& request));
};

}  // namespace testing
}  // namespace bigtable

#endif  // GOOGLE_CLOUD_CPP_BIGTABLE_CLIENT_TESTING_MOCK_DATA_CLIENT_H_
