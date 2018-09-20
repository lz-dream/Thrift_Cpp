// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "RtDataAdapter.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/config.h>
 

#include <thrift/concurrency/ThreadManager.h>    
#include <thrift/concurrency/BoostThreadFactory.h>    
#include <thrift/server/TThreadPoolServer.h>    
#include <thrift/server/TThreadedServer.h>  
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp> 
#include <boost/foreach.hpp>
#include <iostream>
#include "opapi.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using namespace boost::property_tree;
using namespace std;
using namespace  ::cn::oge::kdm::rtdb::thrift::api;

class RtDataAdapterHandler : virtual public RtDataAdapterIf {
 public:

	 string host;
	 int port;
	 int timeout;

  RtDataAdapterHandler() {
    // Your initialization goes here
	  ptree pt;
	  json_parser::read_json("config.json", pt);

	  ptree json_host = pt.get_child("host");
	  host = json_host.get_value<string>();

	  ptree json_port = pt.get_child("port");
	  port = json_port.get_value<int>();

	  ptree json_timeout = pt.get_child("timeout");
	  timeout = json_timeout.get_value<int>();

	  
	  cout << host << ":" << port << endl;
  }

  /**
   * 读取最新数据
   * 
   * @param codes 测点编码列表
   */
  void readLatestData(std::map<std::string, RtSnapshotData> & _return, const std::vector<std::string> & codes) {
    // Your implementation goes here
    printf("readLatestData\n");

	const char* mhost = host.c_str();
	int status = op_init(mhost, port, timeout);
	if (status==0)
	{
		int pointNum = codes.size();
		int* pids = new int[pointNum];

		double* values = new double[pointNum];
		short* status = new short[pointNum];
		long* ptime = new long[pointNum];
		int rc, interval = 0;


		OPGROUPHANDLE gh = new OPGROUPHANDLE();
		gh = op_new_group(pointNum);
		for (int i = 0; i < pointNum; i++)
		{
			op_add_group_point(gh, codes.at(i).c_str());
		}
		rc = op_get_point_id(gh, pids);
		if (rc != 0)
		{
			RtSnapshotData rts;
			RtDataState state;
			rts.__set_state(state.PROCESS_FAIL);
			_return.insert(pair<string, RtSnapshotData>("", rts));
			printf("get point id , connect error\n");
			return;
		}
		rc = op_read_value2(pointNum, pids, values, status, ptime);
		if (rc != 0)
		{
			RtSnapshotData rts;
			RtDataState state;
			rts.__set_state(state.PROCESS_FAIL);
			_return.insert(pair<string, RtSnapshotData>("", rts));
			printf("get values , connect error\n");
			return;
		}
		for (int i = 0; i < pointNum; i++)
		{
			RtSnapshotData rts;
			RtValue rtv;
			rtv.__set_time(ptime[i]);
			rtv.__set_value( values[i]);

			rts.__set_data(rtv);
			_return.insert(map<string, RtSnapshotData>::value_type(codes.at(i), rts));
		} 
		//释放内存
		op_free_group(gh);
		delete[] pids , values , status ,ptime;

	}
  }

  /**
   * 读取原始历史数据
   * 
   * @param codes 测点编码列表
   * 
   * @param startTime 开始时间(自1970年起的毫秒数)
   * 
   * @param endTime 结束时间(自1970年起的毫秒数)(不包含)
   */
  void readHistoryData(std::map<std::string, RtHistoryData> & _return, const std::vector<std::string> & codes, const int64_t startTime, const int64_t endTime) {
    // Your implementation goes here
    printf("readHistoryData\n");
	const char* mhost = host.c_str();
	int status = op_init(mhost, port, timeout);
	if (status == 0)
	{
		int pointNum = codes.size();
		float value;
		short status;
		long ptime;
		short* value_type = new short[pointNum];
		char* types = new char[pointNum];
		PointInfo* points = new PointInfo[pointNum];
		OPRESHANDLE* result = new OPRESHANDLE[pointNum];
		int rc;


		OPGROUPHANDLE gh = op_new_group(pointNum);
		gh = op_new_group(pointNum);
		for (int i = 0; i < pointNum; i++)
		{
			op_add_group_point(gh, codes.at(i).c_str());
			value_type[i] = HIS_VALUE_SAMPLE;
		}
		
		op_get_point_info(gh, points);
		for (int i = 0; i < pointNum; i++)
		{
			types[i] = points[i].record_type;
		}
		rc = op_select_history(gh, types, value_type, startTime / 1000, (endTime / 1000) - 1 , 60, result);
		if (rc != 0) {
			return;
		}
		for (int i = 0; i < pointNum; i++)
		{
			RtHistoryData rth;
			vector<RtValue> rtvs;
			int num = op_num_rows(result[i]);
			cout << codes.at(i) << "-----" << num << endl;
			if (num < 0)
				continue;
			for (int j = 0; j < num; j++)
			{
				RtValue rtv;
				op_fetch_timed_value(result[i], &value, &status, &ptime);
				rtv.__set_time(((int64_t)ptime) * 1000);
				rtv.__set_value(value);
				rtvs.push_back(rtv);
			}
			rth.__set_data(rtvs);
			_return.insert(pair<string, RtHistoryData>(codes.at(i), rth));
		}
	}
  }

  /**
   * 读取插值历史数据
   * 
   * @param codes 测点编码列表
   * 
   * @param startTime 开始时间(自1970年起的毫秒数)
   * 
   * @param endTime 结束时间(自1970年起的毫秒数)(不包含)
   * 
   * @param interval 时间间隔(单位: 秒): 按照默认插值算法对数据进行稀疏或补齐, 以确保数据以此间隔呈现
   */
  void readInterpolationData(std::map<std::string, RtHistoryData> & _return, const std::vector<std::string> & codes, const int64_t startTime, const int64_t endTime, const int32_t interval) {
    // Your implementation goes here
    printf("readInterpolationData\n");
	const char* mhost = host.c_str();
	int status = op_init(mhost, port, timeout);
	if (status == 0)
	{
		int pointNum = codes.size();
		float value;
		short status;
		long ptime;
		short* value_type = new short[pointNum];
		char* types = new char[pointNum];
		PointInfo* points = new PointInfo[pointNum];
		OPRESHANDLE* result = new OPRESHANDLE[pointNum];
		int rc;


		OPGROUPHANDLE gh = op_new_group(pointNum);
		gh = op_new_group(pointNum);
		for (int i = 0; i < pointNum; i++)
		{
			op_add_group_point(gh, codes.at(i).c_str());
			value_type[i] = HIS_VALUE_SAMPLE;
		}

		op_get_point_info(gh, points);
		for (int i = 0; i < pointNum; i++)
		{
			types[i] = points[i].record_type;
		}
		rc = op_select_history(gh, types, value_type, startTime / 1000, (endTime / 1000) - 1, interval, result);
		if (rc != 0) {
			return;
		}
		for (int i = 0; i < pointNum; i++)
		{
			
			RtHistoryData rth;
			vector<RtValue> rtvs;
			int num = op_num_rows(result[i]);
			cout << codes.at(i) << "-----" << num << endl;
			if (num < 0)
				continue;
			for (int j = 0; j < num; j++)
			{
				RtValue rtv;
				op_fetch_timed_value(result[i], &value, &status, &ptime);
				rtv.__set_time(((int64_t)ptime) * 1000);
				rtv.__set_value(value);
				rtvs.push_back(rtv);
			}
			rth.__set_data(rtvs);
			_return.insert(pair<string, RtHistoryData>(codes.at(i), rth));
		}
	}
  }

  /**
   * 读取分段统计数据
   * 
   * @param codes 测点编码列表
   * 
   * @param startTime 开始时间
   * 
   * @param endTime 结束时间(自1970年起的毫秒数)(不包含)
   * 
   * @param types 统计类型
   * 
   * @param segments 所分段数
   */
  void readSummaryData(std::map<std::string, RtSummaryData> & _return, const std::vector<std::string> & codes, const int64_t startTime, const int64_t endTime, const std::set<RtSummaryType::type> & types, const int32_t segments) {
    // Your implementation goes here
    printf("readSummaryData\n");
  }

};

int main(int argc, char **argv) {



  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<RtDataAdapterHandler> handler(new RtDataAdapterHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new RtDataAdapterProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TCompactProtocolFactory());
  try
  {
	  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(10);
	  shared_ptr<PlatformThreadFactory> threadFactory = shared_ptr<PlatformThreadFactory>(new PlatformThreadFactory());
	  threadManager->threadFactory(threadFactory);
	  threadManager->start();
	  TThreadPoolServer server(processor,serverTransport,transportFactory,protocolFactory,threadManager);//使用线程池

	  printf("Starting the server...\n");
	  server.serve();
	  printf("done.\n");
  }
  catch (const std::exception&)
  {

  }


  


  return 0;
}

