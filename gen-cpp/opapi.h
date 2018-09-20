
//																			
//	openPlant database struct/type definitions						
//																			
//////////////////////////////////////////////////////////////////////////////

#ifndef	__OPAPI_H
#define	__OPAPI_H


#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#ifdef OPAPI_EXPORTS
#define OPAPI(type) __declspec(dllexport) type _stdcall
#else
#define OPAPI(type) __declspec(dllimport) type _stdcall
#endif
#else
#define OPAPI(type) type
#endif


// 点的记录类型
#define AX_TYPE				0 		// 模拟类型
#define DX_TYPE				1 		// 数字类型
#define I2_TYPE				2 		// 组合类型
#define I4_TYPE				3 		// 整数类型
#define R8_TYPE				4 		// 双精度类型

// 点的数据来源
#define REAL_POINT			0
#define CALC_POINT			1

// 字符串长度常量
#define OP_PN_LEN			30
#define OP_NAME_LEN			16
#define OP_DESC_LEN			32
#define OP_CHAR_LEN			16
#define OP_EU_LEN			8
#define OP_ST_LEN			6
#define OP_EX_LEN			248     // 计算公式长度

#define OP_TIMEOUT			0x8000	// 点值的超时，如果设置为1，则为超时
#define OP_BAD				0x0300	// 点值的好坏，如果设置为1，则为坏值

// 历史类型及常量
#define HIS_VALUE_AVG  		0 		// 取平均值
#define HIS_VALUE_MAX  		1 		// 取最大值	
#define HIS_VALUE_MIN  		2 		// 取最小值	
#define HIS_VALUE_FLOW 		3 		// 取累计值	
#define HIS_VALUE_STAT 		4 		// 取所有统计值：累计值/最大/最小/累计时间
#define HIS_VALUE_SAMPLE	5 		// 取采样值	
#define HIS_VALUE_SPAN		6 		// 取等间距值	
#define HIS_VALUE_PLOT		7 		// 取PLOT值，每区间包括（起始值，最大值，最小值）	

// 错误代码
#define  OP_SERVERDOWN		-99		// 无法连接服务器。

typedef struct 
{            
	long	tm_tag;
	char 	type;
	short	status;
	union
	{
		char bval;
		short ival;
		long lval;
		float fval;
		double dval;
	} xv;
} PointValue;


// Root info
typedef struct
{
	long		id;						// Root id, for furture extension
	char		name[OP_NAME_LEN+1];	// Root name
	char		desc[OP_DESC_LEN+1];	// Root description
	long		unit_limit;				// Limitation of unit
	long		node_limit;				// Limitation of node
	long		point_limit;			// Limitation of point
} RootInfo;


// Unit Info
typedef struct
{
	long		id;						// Global unit id
	char		name[OP_NAME_LEN+1];	// Unit name
	char		desc[OP_DESC_LEN+1];	// Unit description
} UnitInfo;


// Node info
typedef struct
{
	long		id;						// Global node ID
	long		parent_id;				// Belonged unit ID
	int 		type;
	char		name[OP_NAME_LEN+1];	// Node name
	char		desc[OP_DESC_LEN+1];	// Node description
    int 		freq;
    int 		compress;				// compress or not
	long		access_time;			// access time
} NodeInfo;


// Point Info
typedef struct
{
	// common informations - 17 fields, 138 bytes
	long	id;							//[ID] global point ID
	long	parent_id;					//[ND] belonged node ID
	char	point_type;					//[PT] point type: REAL / CALC
	char	record_type;				//[RT] data type: AX / DX / I2 / I4
	char	name[OP_PN_LEN+1];			//[PN] point name
	char	alias[OP_PN_LEN+1];			//[AN] point alias
	char	desc[OP_DESC_LEN+1];		//[ED] point description
	char	charst[OP_CHAR_LEN+1];		//[KR] characteristics
	short	freq;						//[FQ] sample frequency (in seconds)
	short	ctrl;						//[DU] controller 
	int 	location;					//[HW] hardware address
	char 	channel;					//[BP] point bit
	char	alarm_type;					//[LC] type of alarm check
	char	alarm_prior;				//[AP] alarm priority
	char	archived;					//[SA] save to history or not;
	int 	flags;						//[FL] flags (reserved)
	long    create_time;				//[CT] 
		                                      
	// DX fields - 2 fields, 12 bytes                
	char	set[OP_ST_LEN+1];			//[ST] description of digital point is set
	char	reset[OP_ST_LEN+1];			//[RS] description of digital point is reset
	                                      
	// AX fields - 12 fields, 44 bytes               
	char	eu[OP_EU_LEN+1];			//[EU] name of engineering unit
	short	format;						//[FM] display format 
	float	iv;							//[IV] initial value
	float	bv;							//[BV] bottom scale value
	float	tv;							//[TV] top scale value
	float	ll;							//[LL] low alarm limit
	float	hl;							//[HH] high alarm limit
	float	zl;							//[ZL] low low alarm limit
	float	zh;							//[ZH] high high alarm limit
	float	deadband;					//[DB] default 0.5%
	char	db_type;					//[DT] 0 - PCT, 1 - ENG
	char	comp_type;					//[KZ] 0 - deadband, 1 - linuar
	                                      
	// stat & calc - 4 fields, 6 bytes             
	char	stat_type;					//[TT] use for stat points
	short	period;						//[TP] use for stat points
	short	offset;						//[TO] use for stat points
	char	calc_type;					//[KT] calculate type
	char*	expression;					//[KX] calculate expression
} PointInfo;


typedef struct
{ 
	PointValue  val;
	PointInfo 	info;
} PointData;


typedef struct
{
    int         rid;                	// registry id
	int		    id;						// point id
	char		expression[OP_EX_LEN];	// calc point expression 
} ExInfo;


// Statistics value
typedef struct {
    float       flow;
    float       max;
    float       min;
    float       seconds;
    long      tm_tag;
} StatVal;


typedef void* OPRESHANDLE;
typedef void* OPGROUPHANDLE;

//////////////////////////////////////////////////////////////////////////////

// 函数定义部分


// @函数: op_init()
//		openplant 客户端 API 初始化 
// @参数:
//		opserver:	主机名或IP地址
//		port	:	服务器端口	
//		timeout	:	网络超时(秒)
// @返回值:  0 - 成功, 其它 - 失败
//
OPAPI(int) op_init(const char *opserver, int port=8200, int timeout=30);


// 取服务器时间

OPAPI(int) op_get_system_time(long *t);


// 组操作

OPAPI(OPGROUPHANDLE) op_new_group(int size);

// op_set_group_point 未来将被 op_add_group_point 替代
OPAPI(void) op_set_group_point(OPGROUPHANDLE gh, const char *pname, int i);

OPAPI(void) op_add_group_point(OPGROUPHANDLE gh, const char *pname);

OPAPI(void) op_free_group(OPGROUPHANDLE gh);


// 读节点/点信息

OPAPI(int) op_get_node_id(char *nodename, int *nid);

OPAPI(int) op_get_point_id(OPGROUPHANDLE gh, int *id);

OPAPI(int) op_get_point_type(OPGROUPHANDLE gh, int *id, char *type);

OPAPI(int) op_get_point_info(OPGROUPHANDLE gh, PointInfo *ppi);

OPAPI(int) op_select_node(const char *dbname, OPRESHANDLE *result);

OPAPI(int) op_select_point(const char *nodename, OPRESHANDLE *result);


// 读实时/历史数据

OPAPI(int) op_get_multi_value(OPGROUPHANDLE gh, float *value, short *status);

OPAPI(int) op_get_multi_hist(OPGROUPHANDLE gh, long t, char *type, float *value, short *status);

OPAPI(int) op_select_history(OPGROUPHANDLE gh, char *type, short *value_type,
							long begin_tm, long end_tm, int interval, OPRESHANDLE *results);

OPAPI(int) op_select_history_ex(int *id, int num, short *value_type,
							 long begin_tm, long end_tm, int interval, OPRESHANDLE *results);

// 结果集操作

OPAPI(int) op_num_rows(OPRESHANDLE result);

OPAPI(int) op_fetch_node_info(OPRESHANDLE result, NodeInfo *info);

OPAPI(int) op_fetch_point_info(OPRESHANDLE result, PointInfo *info);

OPAPI(int) op_fetch_timed_value(OPRESHANDLE result, float *value, short *status, long *tm_tag);

OPAPI(int) op_fetch_stat_value(OPRESHANDLE result, StatVal *sval);

OPAPI(void) op_free_result(OPRESHANDLE result);

// 发送实时数据
OPAPI(int) op_send_point_value(int node, int num, int *id, char *type, float *value, long t=0);

OPAPI(int) op_send_point_value2(const char*server, int port, 
								int node, int num, int *id, char *type, double *value, long t=0);
/*
	pt 参数说明：
	pt = AX_TYPE: 所有数据按照AX类型发送数据，内部解析类型。
	pt = DX_TYPE: 所有数据按照DX类型发送数据，内部解析类型。
	pt = I2_TYPE: 所有数据按照I2类型发送数据，内部解析类型。
	pt = I4_TYPE: 所有数据按照I4类型发送数据，内部解析类型。
	pt = R8_TYPE: 所有数据按照R8类型发送数据，内部解析类型。
*/
OPAPI(int) op_send_point_value_ex(int num, int *id, double *value, short *status, long t=0, int pt=0);
OPAPI(int) op_send_point_value_ex2(const char*server, int port,
								  int num, int *id, double *value, short *status, long t=0, int pt=0);


OPAPI(int) op_send_point_value_tm(int num, int *id, double *value, short *status, long *t, int pt=0);
OPAPI(int) op_send_point_value_tm2(const char*server, int port,
								   int num, int *id, double *value, short *status, long *t, int pt=0);



// 新增：读多点实时数据
OPAPI(int) op_read_value2(int num, int *id, double *value, short *status, long *tm_tag);

// 新增：写多点实时数据
OPAPI(int) op_write_value2(int node, int num, int *id, char *type, double *value, long t=0);

// 新增：读多点某一历史时刻的数据
OPAPI(int) op_read_history2(long t, int num, int *id, double *value, short *status);


// 新增：写多点某一历史时刻的数据
OPAPI(int) op_write_history2(long t, int num, int *id, double *value, short *status);

// 新增：写单点某一历史段的数据
OPAPI(int) op_write_history_ex2(int id, int num, long *t, double *value, short *status);


// 
// 向后兼容 OPAPI v1.0
//

// 与 op_send_point_value 一样
OPAPI(int) op_send_point_value1(int node, int num, int *id, char *type, float *value, long t=0);

// 与 op_write_history2 一样, 除了value类型
OPAPI(int) op_write_history1(long t, int num, int *id, float *value, short *status);


// 时间函数

// @函数: decode_time()
//  从 time_t 时间类型转换为：年/月/日/时/分/秒
OPAPI(void) decode_time(long t, int *yy, int *mm, int *dd, int *hh, int *mi, int *ss);


// @函数: encode_time()
//  从年/月/日/时/分/秒转换为 time_t 时间类型
OPAPI(long) encode_time(int yy, int mm, int dd, int hh, int mi, int ss);



#endif		// #ifndef		__OPAPI_H

