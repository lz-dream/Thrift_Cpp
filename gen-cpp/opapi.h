
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


// ��ļ�¼����
#define AX_TYPE				0 		// ģ������
#define DX_TYPE				1 		// ��������
#define I2_TYPE				2 		// �������
#define I4_TYPE				3 		// ��������
#define R8_TYPE				4 		// ˫��������

// ���������Դ
#define REAL_POINT			0
#define CALC_POINT			1

// �ַ������ȳ���
#define OP_PN_LEN			30
#define OP_NAME_LEN			16
#define OP_DESC_LEN			32
#define OP_CHAR_LEN			16
#define OP_EU_LEN			8
#define OP_ST_LEN			6
#define OP_EX_LEN			248     // ���㹫ʽ����

#define OP_TIMEOUT			0x8000	// ��ֵ�ĳ�ʱ���������Ϊ1����Ϊ��ʱ
#define OP_BAD				0x0300	// ��ֵ�ĺû����������Ϊ1����Ϊ��ֵ

// ��ʷ���ͼ�����
#define HIS_VALUE_AVG  		0 		// ȡƽ��ֵ
#define HIS_VALUE_MAX  		1 		// ȡ���ֵ	
#define HIS_VALUE_MIN  		2 		// ȡ��Сֵ	
#define HIS_VALUE_FLOW 		3 		// ȡ�ۼ�ֵ	
#define HIS_VALUE_STAT 		4 		// ȡ����ͳ��ֵ���ۼ�ֵ/���/��С/�ۼ�ʱ��
#define HIS_VALUE_SAMPLE	5 		// ȡ����ֵ	
#define HIS_VALUE_SPAN		6 		// ȡ�ȼ��ֵ	
#define HIS_VALUE_PLOT		7 		// ȡPLOTֵ��ÿ�����������ʼֵ�����ֵ����Сֵ��	

// �������
#define  OP_SERVERDOWN		-99		// �޷����ӷ�������

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

// �������岿��


// @����: op_init()
//		openplant �ͻ��� API ��ʼ�� 
// @����:
//		opserver:	��������IP��ַ
//		port	:	�������˿�	
//		timeout	:	���糬ʱ(��)
// @����ֵ:  0 - �ɹ�, ���� - ʧ��
//
OPAPI(int) op_init(const char *opserver, int port=8200, int timeout=30);


// ȡ������ʱ��

OPAPI(int) op_get_system_time(long *t);


// �����

OPAPI(OPGROUPHANDLE) op_new_group(int size);

// op_set_group_point δ������ op_add_group_point ���
OPAPI(void) op_set_group_point(OPGROUPHANDLE gh, const char *pname, int i);

OPAPI(void) op_add_group_point(OPGROUPHANDLE gh, const char *pname);

OPAPI(void) op_free_group(OPGROUPHANDLE gh);


// ���ڵ�/����Ϣ

OPAPI(int) op_get_node_id(char *nodename, int *nid);

OPAPI(int) op_get_point_id(OPGROUPHANDLE gh, int *id);

OPAPI(int) op_get_point_type(OPGROUPHANDLE gh, int *id, char *type);

OPAPI(int) op_get_point_info(OPGROUPHANDLE gh, PointInfo *ppi);

OPAPI(int) op_select_node(const char *dbname, OPRESHANDLE *result);

OPAPI(int) op_select_point(const char *nodename, OPRESHANDLE *result);


// ��ʵʱ/��ʷ����

OPAPI(int) op_get_multi_value(OPGROUPHANDLE gh, float *value, short *status);

OPAPI(int) op_get_multi_hist(OPGROUPHANDLE gh, long t, char *type, float *value, short *status);

OPAPI(int) op_select_history(OPGROUPHANDLE gh, char *type, short *value_type,
							long begin_tm, long end_tm, int interval, OPRESHANDLE *results);

OPAPI(int) op_select_history_ex(int *id, int num, short *value_type,
							 long begin_tm, long end_tm, int interval, OPRESHANDLE *results);

// ���������

OPAPI(int) op_num_rows(OPRESHANDLE result);

OPAPI(int) op_fetch_node_info(OPRESHANDLE result, NodeInfo *info);

OPAPI(int) op_fetch_point_info(OPRESHANDLE result, PointInfo *info);

OPAPI(int) op_fetch_timed_value(OPRESHANDLE result, float *value, short *status, long *tm_tag);

OPAPI(int) op_fetch_stat_value(OPRESHANDLE result, StatVal *sval);

OPAPI(void) op_free_result(OPRESHANDLE result);

// ����ʵʱ����
OPAPI(int) op_send_point_value(int node, int num, int *id, char *type, float *value, long t=0);

OPAPI(int) op_send_point_value2(const char*server, int port, 
								int node, int num, int *id, char *type, double *value, long t=0);
/*
	pt ����˵����
	pt = AX_TYPE: �������ݰ���AX���ͷ������ݣ��ڲ��������͡�
	pt = DX_TYPE: �������ݰ���DX���ͷ������ݣ��ڲ��������͡�
	pt = I2_TYPE: �������ݰ���I2���ͷ������ݣ��ڲ��������͡�
	pt = I4_TYPE: �������ݰ���I4���ͷ������ݣ��ڲ��������͡�
	pt = R8_TYPE: �������ݰ���R8���ͷ������ݣ��ڲ��������͡�
*/
OPAPI(int) op_send_point_value_ex(int num, int *id, double *value, short *status, long t=0, int pt=0);
OPAPI(int) op_send_point_value_ex2(const char*server, int port,
								  int num, int *id, double *value, short *status, long t=0, int pt=0);


OPAPI(int) op_send_point_value_tm(int num, int *id, double *value, short *status, long *t, int pt=0);
OPAPI(int) op_send_point_value_tm2(const char*server, int port,
								   int num, int *id, double *value, short *status, long *t, int pt=0);



// �����������ʵʱ����
OPAPI(int) op_read_value2(int num, int *id, double *value, short *status, long *tm_tag);

// ������д���ʵʱ����
OPAPI(int) op_write_value2(int node, int num, int *id, char *type, double *value, long t=0);

// �����������ĳһ��ʷʱ�̵�����
OPAPI(int) op_read_history2(long t, int num, int *id, double *value, short *status);


// ������д���ĳһ��ʷʱ�̵�����
OPAPI(int) op_write_history2(long t, int num, int *id, double *value, short *status);

// ������д����ĳһ��ʷ�ε�����
OPAPI(int) op_write_history_ex2(int id, int num, long *t, double *value, short *status);


// 
// ������ OPAPI v1.0
//

// �� op_send_point_value һ��
OPAPI(int) op_send_point_value1(int node, int num, int *id, char *type, float *value, long t=0);

// �� op_write_history2 һ��, ����value����
OPAPI(int) op_write_history1(long t, int num, int *id, float *value, short *status);


// ʱ�亯��

// @����: decode_time()
//  �� time_t ʱ������ת��Ϊ����/��/��/ʱ/��/��
OPAPI(void) decode_time(long t, int *yy, int *mm, int *dd, int *hh, int *mi, int *ss);


// @����: encode_time()
//  ����/��/��/ʱ/��/��ת��Ϊ time_t ʱ������
OPAPI(long) encode_time(int yy, int mm, int dd, int hh, int mi, int ss);



#endif		// #ifndef		__OPAPI_H

