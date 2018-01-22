// ManagedPluginHelper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define PLUGINNAME     L"Managed Plugin Helper"
#define VERSION        L"1.0.0.0"

static HINSTANCE hdllinst;
static std::vector<t_menu> mainmenu_dynamic;
int mainmenu_open_api_list(struct t_table* ptable, wchar_t* name, ulong index, int mode);
static t_menu* managed_plugins_menu;

typedef struct {
	wchar_t* functionName;
	void* functionAddress;
} function_record;

function_record* function_records = new function_record[353]
{
	{ L"Absolutizepath"                                       ,    Absolutizepath },
	{ L"Activatetablewindow"                                  ,    Activatetablewindow },
	{ L"Addjump"                                              ,    Addjump },
	{ L"Addnesteddata"                                        ,    Addnesteddata },
	{ L"Addprotocolrange"                                     ,    Addprotocolrange },
	{ L"Addrange"                                             ,    Addrange },
	{ L"Addsimpledata"                                        ,    Addsimpledata },
	{ L"Addsorteddata"                                        ,    Addsorteddata },
	{ L"Addstringtocombolist"                                 ,    Addstringtocombolist },
	{ L"Addtohistory"                                         ,    Addtohistory },
	{ L"Addtolist"                                            ,    Addtolist },
	{ L"Addtosettings"                                        ,    Addtosettings },
	{ L"Alignselection"                                       ,    Alignselection },
	{ L"Arelocaljumpscallstorange"                            ,    Arelocaljumpscallstorange },
	{ L"Asciitounicode"                                       ,    Asciitounicode },
	{ L"Asmindump"                                            ,    Asmindump },
	{ L"Assemble"                                             ,    Assemble },
	{ L"Assembleallforms"                                     ,    Assembleallforms },
	{ L"Backupusercode"                                       ,    Backupusercode },
	{ L"Binaryedit"                                           ,    Binaryedit },
	{ L"Bitcount"                                             ,    Bitcount },
	{ L"Broadcast"                                            ,    Broadcast },
	{ L"Browsecodelocations"                                  ,    Browsecodelocations },
	{ L"Browsedirectory"                                      ,    Browsedirectory },
	{ L"Browsefilename"                                       ,    Browsefilename },
	{ L"Byteregtodwordreg"                                    ,    Byteregtodwordreg },
	{ L"Callmenufunction"                                     ,    Callmenufunction },
	{ L"Cexpression"                                          ,    Cexpression },
	{ L"Checkcondition"                                       ,    Checkcondition },
	{ L"Checkfordebugevent"                                   ,    Checkfordebugevent },
	{ L"Checkhistory"                                         ,    Checkhistory },
	//{ L"Clearfpu"                                             ,    Clearfpu }, Unresolved
	{ L"Closeprocess"                                         ,    Closeprocess },
	//{ L"Closetaggedfile"                                      ,    Closetaggedfile },
	{ L"Cmdinfo"                                              ,    Cmdinfo },
	{ L"Commentaddress"                                       ,    Commentaddress },
	{ L"Commentcharacter"                                     ,    Commentcharacter },
	{ L"Comparecommand"                                       ,    Comparecommand },
	{ L"Comparesequence"                                      ,    Comparesequence },
	{ L"Compress"                                             ,    Compress },
	{ L"Condbreakpoint"                                       ,    Condbreakpoint },
	{ L"Conderror"                                            ,    Conderror },
	{ L"Condlogbreakpoint"                                    ,    Condlogbreakpoint },
	{ L"Condyesno"                                            ,    Condyesno },
	{ L"Confirmhardwarebreakpoint"                            ,    Confirmhardwarebreakpoint },
	{ L"Confirmint3breakpoint"                                ,    Confirmint3breakpoint },
	{ L"Confirmint3breakpointlist"                            ,    Confirmint3breakpointlist },
	{ L"Confirmoverwrite"                                     ,    Confirmoverwrite },
	{ L"Confirmsorteddata"                                    ,    Confirmsorteddata },
	{ L"Copydumpselection"                                    ,    Copydumpselection },
	{ L"Copymemoryhex"                                        ,    Copymemoryhex },
	{ L"Copytableselection"                                   ,    Copytableselection },
	{ L"Copywholetable"                                       ,    Copywholetable },
	//{ L"CRCcalc"                                              ,    CRCcalc }, Unresolved
	{ L"Createdumpwindow"                                     ,    Createdumpwindow },
	{ L"Createframewindow"                                    ,    Createframewindow },
	{ L"Createnesteddata"                                     ,    Createnesteddata },
	{ L"Createottablewindow"                                  ,    Createottablewindow },
	{ L"Createsimpledata"                                     ,    Createsimpledata },
	{ L"Createsorteddata"                                     ,    Createsorteddata },
	{ L"Createtablechild"                                     ,    Createtablechild },
	{ L"Createtablewindow"                                    ,    Createtablewindow },
	{ L"Createtabwindow"                                      ,    Createtabwindow },
	//{ L"Createtaggedfile"                                     ,    Createtaggedfile },
	{ L"Decodeaddress"                                        ,    Decodeaddress },
	{ L"Decodearglocal"                                       ,    Decodearglocal },
	{ L"Decodeargument"                                       ,    Decodeargument },
	{ L"Decodeknownbyaddr"                                    ,    Decodeknownbyaddr },
	{ L"Decodeknownbyname"                                    ,    Decodeknownbyname },
	{ L"Decoderange"                                          ,    Decoderange },
	{ L"Decoderelativeoffset"                                 ,    Decoderelativeoffset },
	{ L"Decodestructure"                                      ,    Decodestructure },
	{ L"Decodethreadname"                                     ,    Decodethreadname },
	{ L"Decodetype"                                           ,    Decodetype },
	{ L"Decompress"                                           ,    Decompress },
	{ L"Defaultactions"                                       ,    Defaultactions },
	{ L"Defaultbar"                                           ,    Defaultbar },
	{ L"Delayedtableredraw"                                   ,    Delayedtableredraw },
	{ L"Deletedatarange"                                      ,    Deletedatarange },
	{ L"Deletedatarangelist"                                  ,    Deletedatarangelist },
	{ L"Deleteinisection"                                     ,    Deleteinisection },
	{ L"Deletenestedrange"                                    ,    Deletenestedrange },
	{ L"Deletenonconfirmedsorteddata"                         ,    Deletenonconfirmedsorteddata },
	{ L"Deletesimpledatarange"                                ,    Deletesimpledatarange },
	{ L"Deletesorteddata"                                     ,    Deletesorteddata },
	{ L"Deletesorteddatarange"                                ,    Deletesorteddatarange },
	{ L"DemanglenameW"                                        ,    DemanglenameW },
	{ L"Destroynesteddata"                                    ,    Destroynesteddata },
	{ L"Destroysimpledata"                                    ,    Destroysimpledata },
	{ L"Destroysorteddata"                                    ,    Destroysorteddata },
	{ L"Detachprocess"                                        ,    Detachprocess },
	{ L"Devicenametodosname"                                  ,    Devicenametodosname },
	{ L"Disasm"                                               ,    Disasm },
	{ L"Disassembleback"                                      ,    Disassembleback },
	{ L"Disassembleforward"                                   ,    Disassembleforward },
	//{ L"Div64by32"                                            ,    Div64by32 }, Unresolved
	{ L"Dumpback"                                             ,    Dumpback },
	{ L"Dumpforward"                                          ,    Dumpforward },
	{ L"Editmemory"                                           ,    Editmemory },
	{ L"Eexpression"                                          ,    Eexpression },
	{ L"Embeddumpwindow"                                      ,    Embeddumpwindow },
	{ L"Emptyrange"                                           ,    Emptyrange },
	{ L"Enablehardbreakpoint"                                 ,    Enablehardbreakpoint },
	{ L"Enableint3breakpoint"                                 ,    Enableint3breakpoint },
	{ L"Enablemembreakpoint"                                  ,    Enablemembreakpoint },
	{ L"Ensurememorybackup"                                   ,    Ensurememorybackup },
	{ L"Error"                                                ,    Error },
	{ L"Exprcount"                                            ,    Exprcount },
	{ L"Expression"                                           ,    Expression },
	{ L"Fastexpression"                                       ,    Fastexpression },
	{ L"Filefromini"                                          ,    Filefromini },
	{ L"Filenamefromhandle"                                   ,    Filenamefromhandle },
	{ L"Filetoini"                                            ,    Filetoini },
	{ L"Fillcombowithcodepages"                               ,    Fillcombowithcodepages },
	{ L"Fillcombowithgroup"                                   ,    Fillcombowithgroup },
	{ L"Fillcombowithstruct"                                  ,    Fillcombowithstruct },
	//{ L"Finalizetaggedfile"                                   ,    Finalizetaggedfile },
	{ L"FindaddressW"                                         ,    FindaddressW },
	{ L"Findcontrol"                                          ,    Findcontrol },
	{ L"Finddata"                                             ,    Finddata },
	{ L"Finddataptr"                                          ,    Finddataptr },
	{ L"Finddecode"                                           ,    Finddecode },
	{ L"Findfiledump"                                         ,    Findfiledump },
	{ L"Findfileoffset"                                       ,    Findfileoffset },
	{ L"Findfixup"                                            ,    Findfixup },
	{ L"Findfreehardbreakslot"                                ,    Findfreehardbreakslot },
	{ L"Findglobalcallsto"                                    ,    Findglobalcallsto },
	{ L"Findglobaljumpscallsto"                               ,    Findglobaljumpscallsto },
	{ L"Findjumpfrom"                                         ,    Findjumpfrom },
	{ L"Findlabel"                                            ,    Findlabel },
	{ L"Findlocaljumpscallsto"                                ,    Findlocaljumpscallsto },
	{ L"Findlocaljumpsto"                                     ,    Findlocaljumpsto },
	{ L"Findmainmodule"                                       ,    Findmainmodule },
	{ L"Findmemory"                                           ,    Findmemory },
	{ L"Findmodule"                                           ,    Findmodule },
	{ L"Findmodulebyname"                                     ,    Findmodulebyname },
	{ L"FindnameW"                                            ,    FindnameW },
	{ L"Findnesteddata"                                       ,    Findnesteddata },
	{ L"Findnextdata"                                         ,    Findnextdata },
	{ L"Findnextdatalist"                                     ,    Findnextdatalist },
	{ L"FindnextnamelistW"                                    ,    FindnextnamelistW },
	{ L"FindnextnameW"                                        ,    FindnextnameW },
	{ L"Findretaddrdata"                                      ,    Findretaddrdata },
	{ L"Findruntracerecord"                                   ,    Findruntracerecord },
	{ L"Findsimpledata"                                       ,    Findsimpledata },
	{ L"Findsorteddata"                                       ,    Findsorteddata },
	{ L"Findsorteddatarange"                                  ,    Findsorteddatarange },
	{ L"Findsortedindexrange"                                 ,    Findsortedindexrange },
	{ L"Findsource"                                           ,    Findsource },
	{ L"Findstructureitembyoffset"                            ,    Findstructureitembyoffset },
	{ L"Findthread"                                           ,    Findthread },
	{ L"Findthreadbyordinal"                                  ,    Findthreadbyordinal },
	{ L"Flash"                                                ,    Flash },
	{ L"Flushmemorycache"                                     ,    Flushmemorycache },
	{ L"Followcall"                                           ,    Followcall },
	{ L"Fullrange"                                            ,    Fullrange },
	{ L"Get3dnow"                                             ,    Get3dnow },
	{ L"Getactiveframe"                                       ,    Getactiveframe },
	{ L"Getactivetab"                                         ,    Getactivetab },
	{ L"Getaddressrange"                                      ,    Getaddressrange },
	{ L"Getanalysercomment"                                   ,    Getanalysercomment },
	{ L"Getasmsearchmodel"                                    ,    Getasmsearchmodel },
	{ L"Getcharacterwidth"                                    ,    Getcharacterwidth },
	{ L"Getconstantbyname"                                    ,    Getconstantbyname },
	{ L"Getconstantbyvalue"                                   ,    Getconstantbyvalue },
	{ L"Getcpudisasmdump"                                     ,    Getcpudisasmdump },
	{ L"Getcpudisasmselection"                                ,    Getcpudisasmselection },
	{ L"Getcpudisasmtable"                                    ,    Getcpudisasmtable },
	//{ L"Getcpuidfeatures"                                     ,    Getcpuidfeatures }, Unresolved
	{ L"Getcpuruntracebackstep"                               ,    Getcpuruntracebackstep },
	{ L"Getcputhreadid"                                       ,    Getcputhreadid },
	{ L"Getdword"                                             ,    Getdword },
	{ L"Getdwordexpression"                                   ,    Getdwordexpression },
	{ L"Getexceptionrange"                                    ,    Getexceptionrange },
	{ L"Getexeversion"                                        ,    Getexeversion },
	{ L"Getexportfrommemory"                                  ,    Getexportfrommemory },
	{ L"Getextproclimits"                                     ,    Getextproclimits },
	{ L"Getfloat"                                             ,    Getfloat },
	{ L"Getfpureg"                                            ,    Getfpureg },
	{ L"Getfromini"                                           ,    Getfromini },
	{ L"Getfromsettings"                                      ,    Getfromsettings },
	{ L"Getgotoexpression"                                    ,    Getgotoexpression },
	{ L"Getguidname"                                          ,    Getguidname },
	{ L"Getindexbypredefinedtype"                             ,    Getindexbypredefinedtype },
	{ L"Getinteger"                                           ,    Getinteger },
	{ L"Getlasterror"                                         ,    Getlasterror },
	{ L"Getlasterrorcode"                                     ,    Getlasterrorcode },
	{ L"Getloopcomment"                                       ,    Getloopcomment },
	{ L"Getmmx"                                               ,    Getmmx },
	{ L"Getmodulestring"                                      ,    Getmodulestring },
	{ L"Getnestingdepth"                                      ,    Getnestingdepth },
	{ L"Getnestingpattern"                                    ,    Getnestingpattern },
	{ L"Getoriginaldatasize"                                  ,    Getoriginaldatasize },
	{ L"Getpackednetint"                                      ,    Getpackednetint },
	{ L"Getpredefinedtypebyindex"                             ,    Getpredefinedtypebyindex },
	{ L"Getproccomment"                                       ,    Getproccomment },
	{ L"Getproclimits"                                        ,    Getproclimits },
	{ L"Getrangebyindex"                                      ,    Getrangebyindex },
	{ L"Getrangebymember"                                     ,    Getrangebymember },
	{ L"Getrangecount"                                        ,    Getrangecount },
	{ L"Getrawdata"                                           ,    Getrawdata },
	{ L"Getregister"                                          ,    Getregister },
	{ L"Getruntrace"                                          ,    Getruntrace },
	{ L"Getseqsearchmodel"                                    ,    Getseqsearchmodel },
	{ L"Getsetcount"                                          ,    Getsetcount },
	{ L"Getsimpledatabyindex"                                 ,    Getsimpledatabyindex },
	{ L"Getsimpledataindexbyaddr"                             ,    Getsimpledataindexbyaddr },
	{ L"Getsortedbyindex"                                     ,    Getsortedbyindex },
	{ L"Getsortedbyselection"                                 ,    Getsortedbyselection },
	{ L"Getsourceline"                                        ,    Getsourceline },
	{ L"Getsse"                                               ,    Getsse },
	{ L"Getstring"                                            ,    Getstring },
	{ L"Getstructureitemcount"                                ,    Getstructureitemcount },
	{ L"Getstructureitemvalue"                                ,    Getstructureitemvalue },
	{ L"Getstructuretype"                                     ,    Getstructuretype },
	{ L"Getswitchcomment"                                     ,    Getswitchcomment },
	{ L"Gettabcount"                                          ,    Gettabcount },
	{ L"Gettableselectionxy"                                  ,    Gettableselectionxy },
	{ L"Gettabletext"                                         ,    Gettabletext },
	//{ L"Gettaggedfiledata"                                    ,    Gettaggedfiledata },
	//{ L"Gettaggedrecordsize"                                  ,    Gettaggedrecordsize },
	{ L"Guardmemory"                                          ,    Guardmemory },
	{ L"Guidtotext"                                           ,    Guidtotext },
	{ L"Hardbreakpoint"                                       ,    Hardbreakpoint },
	{ L"Hardlogbreakpoint"                                    ,    Hardlogbreakpoint },
	{ L"Heapsort"                                             ,    Heapsort },
	{ L"Heapsortex"                                           ,    Heapsortex },
	{ L"HexdumpA"                                             ,    HexdumpA },
	{ L"HexdumpW"                                             ,    HexdumpW },
	{ L"Hexprint4A"                                           ,    Hexprint4A },
	{ L"Hexprint4W"                                           ,    Hexprint4W },
	{ L"Hexprint8A"                                           ,    Hexprint8A },
	{ L"Hexprint8W"                                           ,    Hexprint8W },
	{ L"HexprintA"                                            ,    HexprintA },
	{ L"HexprintW"                                            ,    HexprintW },
	{ L"Info"                                                 ,    Info },
	{ L"Initset"                                              ,    Initset },
	{ L"Insertdata"                                           ,    Insertdata },
	{ L"InsertnameW"                                          ,    InsertnameW },
	{ L"Isdataavailable"                                      ,    Isdataavailable },
	{ L"Isdatainrange"                                        ,    Isdatainrange },
	{ L"Isguid"                                               ,    Isguid },
	{ L"Isinset"                                              ,    Isinset },
	{ L"Isnoreturn"                                           ,    Isnoreturn },
	{ L"Isretaddr"                                            ,    Isretaddr },
	{ L"Issortedinit"                                         ,    Issortedinit },
	{ L"Isstring"                                             ,    Isstring },
	{ L"Issystem"                                             ,    Issystem },
	{ L"Iszero"                                               ,    Iszero },
	{ L"Labeladdress"                                         ,    Labeladdress },
	{ L"Linecount"                                            ,    Linecount },
	{ L"Listmemory"                                           ,    Listmemory },
	{ L"Maketableareavisible"                                 ,    Maketableareavisible },
	//{ L"Maskfpu"                                              ,    Maskfpu }, Unresolved
	{ L"Maybecommand"                                         ,    Maybecommand },
	{ L"Memalloc"                                             ,    Memalloc },
	{ L"Membreakpoint"                                        ,    Membreakpoint },
	{ L"Memdouble"                                            ,    Memdouble },
	{ L"Memfree"                                              ,    Memfree },
	{ L"Memlogbreakpoint"                                     ,    Memlogbreakpoint },
	{ L"Mempurge"                                             ,    Mempurge },
	{ L"Mergequickdata"                                       ,    Mergequickdata },
	{ L"Message"                                              ,    Message },
	{ L"Moveprogress"                                         ,    Moveprogress },
	{ L"Movetableselection"                                   ,    Movetableselection },
	{ L"Nameoffloat"                                          ,    Nameoffloat },
	{ L"Ndisasm"                                              ,    Ndisasm },
	{ L"Nesteddatatoudd"                                      ,    Nesteddatatoudd },
	{ L"Newdumpselection"                                     ,    Newdumpselection },
	//{ L"Opentaggedfile"                                       ,    Opentaggedfile },
	{ L"Optostring"                                           ,    Optostring },
	{ L"Pastememoryhex"                                       ,    Pastememoryhex },
	{ L"Pauseprocess"                                         ,    Pauseprocess },
	{ L"Plugingetuniquedatatype"                              ,    Plugingetuniquedatatype },
	{ L"Pluginmodulechanged"                                  ,    Pluginmodulechanged },
	{ L"Pluginpackedrecord"                                   ,    Pluginpackedrecord },
	{ L"Pluginsaverecord"                                     ,    Pluginsaverecord },
	{ L"Pluginshowoptions"                                    ,    Pluginshowoptions },
	{ L"Plugintempbreakpoint"                                 ,    Plugintempbreakpoint },
	{ L"Preparedialog"                                        ,    Preparedialog },
	{ L"Printfloat10"                                         ,    Printfloat10 },
	{ L"Printfloat4"                                          ,    Printfloat4 },
	{ L"Printfloat8"                                          ,    Printfloat8 },
	{ L"Printmmx"                                             ,    Printmmx },
	{ L"Progress"                                             ,    Progress },
	{ L"Quickinsertdata"                                      ,    Quickinsertdata },
	{ L"QuickinsertnameW"                                     ,    QuickinsertnameW },
	{ L"Quicktimerflush"                                      ,    Quicktimerflush },
	{ L"Quicktimerstart"                                      ,    Quicktimerstart },
	{ L"Quicktimerstop"                                       ,    Quicktimerstop },
	{ L"Readfile"                                             ,    Readfile },
	{ L"Readmemory"                                           ,    Readmemory },
	{ L"Readmemoryex"                                         ,    Readmemoryex },
	{ L"Redrawcpudisasm"                                      ,    Redrawcpudisasm },
	{ L"Redrawcpureg"                                         ,    Redrawcpureg },
	{ L"Redrawlist"                                           ,    Redrawlist },
	{ L"Registermodifiedbyuser"                               ,    Registermodifiedbyuser },
	{ L"Relativizepath"                                       ,    Relativizepath },
	{ L"Removeanalysis"                                       ,    Removeanalysis },
	{ L"Removehardbreakpoint"                                 ,    Removehardbreakpoint },
	{ L"Removeint3breakpoint"                                 ,    Removeint3breakpoint },
	{ L"Removemembreakpoint"                                  ,    Removemembreakpoint },
	{ L"Removerange"                                          ,    Removerange },
	{ L"Removetableselection"                                 ,    Removetableselection },
	{ L"Renumeratesorteddata"                                 ,    Renumeratesorteddata },
	{ L"Replacegraphs"                                        ,    Replacegraphs },
	{ L"Replacesorteddatarange"                               ,    Replacesorteddatarange },
	//{ L"Restoredialogposition"                                ,    Restoredialogposition },
	{ L"Resumeallthreads"                                     ,    Resumeallthreads },
	{ L"Run"                                                  ,    Run },
	//{ L"Savedialogposition"                                   ,    Savedialogposition },
	//{ L"Savepackedrecord"                                     ,    Savepackedrecord },
	//{ L"Savetaggedrecord"                                     ,    Savetaggedrecord },
	{ L"Scan"                                                 ,    Scan },
	{ L"Scrolldumpwindow"                                     ,    Scrolldumpwindow },
	{ L"Setactivetab"                                         ,    Setactivetab },
	{ L"Setautoupdate"                                        ,    Setautoupdate },
	//{ L"SetcaseA"                                             ,    SetcaseA }, Unresolved
	//{ L"SetcaseW"                                             ,    SetcaseW }, Unresolved
	{ L"Setcondition"                                         ,    Setcondition },
	{ L"Setcpu"                                               ,    Setcpu },
	{ L"Setdumptype"                                          ,    Setdumptype },
	{ L"Sethardbreakpoint"                                    ,    Sethardbreakpoint },
	{ L"Setint3breakpoint"                                    ,    Setint3breakpoint },
	{ L"Setmembreakpoint"                                     ,    Setmembreakpoint },
	{ L"Setrtcond"                                            ,    Setrtcond },
	{ L"Setrtprot"                                            ,    Setrtprot },
	{ L"Setstatus"                                            ,    Setstatus },
	{ L"Settableselection"                                    ,    Settableselection },
	{ L"Showsourcecode"                                       ,    Showsourcecode },
	{ L"SignedhexA"                                           ,    SignedhexA },
	{ L"SignedhexW"                                           ,    SignedhexW },
	{ L"Simpleaddress"                                        ,    Simpleaddress },
	{ L"Skipspaces"                                           ,    Skipspaces },
	{ L"Sortjumpdata"                                         ,    Sortjumpdata },
	{ L"Sortsimpledata"                                       ,    Sortsimpledata },
	{ L"Sortsorteddata"                                       ,    Sortsorteddata },
	{ L"Squeezename"                                          ,    Squeezename },
	{ L"Startnextdata"                                        ,    Startnextdata },
	{ L"Startnextdatalist"                                    ,    Startnextdatalist },
	{ L"Startnextnamelist"                                    ,    Startnextnamelist },
	//{ L"StrcmpW"                                              ,    StrcmpW }, Unresolved
	{ L"StrcopyA"                                             ,    StrcopyA },
	{ L"StrcopyW"                                             ,    StrcopyW },
	//{ L"StrcopycaseA"                                         ,    StrcopycaseA }, Unresolved
	//{ L"StrcopycaseW"                                         ,    StrcopycaseW }, Unresolved
	{ L"Stringfromini"                                        ,    Stringfromini },
	{ L"Stringtotext"                                         ,    Stringtotext },
	{ L"StrlenA"                                              ,    StrlenA },
	{ L"StrlenW"                                              ,    StrlenW },
	//{ L"StrnstrA"                                             ,    StrnstrA }, Unresolved
	//{ L"StrnstrW"                                             ,    StrnstrW }, Unresolved
	{ L"Substitutehkeyprefix"                                 ,    Substitutehkeyprefix },
	{ L"Suspendallthreads"                                    ,    Suspendallthreads },
	{ L"Swapmem"                                              ,    Swapmem },
	{ L"Swprintf"                                             ,    Swprintf },
	{ L"Tempinfo"                                             ,    Tempinfo },
	{ L"Threadregisters"                                      ,    Threadregisters },
	{ L"Uddtonesteddata"                                      ,    Uddtonesteddata },
	{ L"Uncapitalize"                                         ,    Uncapitalize },
	{ L"Unicodebuffertoascii"                                 ,    Unicodebuffertoascii },
	{ L"Unicodetoascii"                                       ,    Unicodetoascii },
	{ L"Unicodetoutf"                                         ,    Unicodetoutf },
	{ L"Unmarknewsorteddata"                                  ,    Unmarknewsorteddata },
	{ L"Updateframe"                                          ,    Updateframe },
	{ L"Updatetable"                                          ,    Updatetable },
	{ L"Updatetabs"                                           ,    Updatetabs },
	{ L"Utftounicode"                                         ,    Utftounicode },
	{ L"Virtalloc"                                            ,    Virtalloc },
	{ L"Virtfree"                                             ,    Virtfree },
	{ L"Walkhistory"                                          ,    Walkhistory },
	{ L"Wipebreakpointrange"                                  ,    Wipebreakpointrange },
	{ L"Writememory"                                          ,    Writememory },
	{ L"Writetoini"                                           ,    Writetoini },
	{ NULL, NULL }
};

BOOL WINAPI DllEntryPoint(HINSTANCE hi, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH)
		hdllinst = hi;
	return 1;
};

extc int __cdecl ODBG2_Pluginquery(
	int ollydbgversion, 
	ulong *features,
	wchar_t pluginname[SHORTNAME], 
	wchar_t pluginversion[SHORTNAME]) 
{
	if (ollydbgversion < 201)
		return 0;

	wcscpy(pluginname, PLUGINNAME);
	wcscpy(pluginversion, VERSION);
	return PLUGIN_VERSION;
};

extc int __cdecl ODBG2_Plugininit(void) {
	
	ICLRMetaHost* pMetaHost = NULL;
	HRESULT hr;
	/* Get ICLRMetaHost instance */
	hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (VOID**)&pMetaHost);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] CLRCreateInstance(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	ICLRRuntimeInfo* pRuntimeInfo = NULL;
	/* Get ICLRRuntimeInfo instance */
	hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (VOID**)&pRuntimeInfo);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pMetaHost->GetRuntime(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	BOOL bLoadable;
	/* Check if the specified runtime can be loaded */
	hr = pRuntimeInfo->IsLoadable(&bLoadable);
	if (FAILED(hr) || !bLoadable)
	{
		MessageBox(NULL, L"[!] pRuntimeInfo->IsLoadable(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	ICorRuntimeHost* pRuntimeHost = NULL;
	/* Get ICorRuntimeHost instance */
	hr = pRuntimeInfo->GetInterface(CLSID_CorRuntimeHost, IID_ICorRuntimeHost, (VOID**)&pRuntimeHost);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeInfo->GetInterface(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	/* Start the CLR */
	hr = pRuntimeHost->Start();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeHost->Start() failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	IUnknownPtr pAppDomainThunk = NULL;
	hr = pRuntimeHost->GetDefaultDomain(&pAppDomainThunk);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeHost->GetDefaultDomain(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	_AppDomainPtr pDefaultAppDomain = NULL;
	/* Equivalent of System.AppDomain.CurrentDomain in C# */
	hr = pAppDomainThunk->QueryInterface(__uuidof(_AppDomain), (VOID**)&pDefaultAppDomain);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAppDomainThunk->QueryInterface(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	_AssemblyPtr pAssembly = NULL;

	FILE * pFile;
	long lSize;
	void *buffer;
	size_t result;

	pFile = fopen("ManagedPluginLoader.dll", "rb");
	if (pFile == NULL)
	{
		MessageBox(NULL, L"[!] fopen(\"ManagedPluginLoader.dll\") failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = CoTaskMemAlloc(lSize);
	if (buffer == NULL)
	{
		MessageBox(NULL, L"[!] malloc(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	SAFEARRAYBOUND bounds = { lSize, 0 };

	SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, &bounds);
	void* data;
	SafeArrayAccessData(psa, &data);
	CopyMemory(data, buffer, lSize);
	CoTaskMemFree(buffer);
	buffer = nullptr;

	SafeArrayUnaccessData(psa);

	hr = pDefaultAppDomain->Load_3(psa, &pAssembly);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pDefaultAppDomain->Load_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	_TypePtr pManagedPluginLoaderType = NULL;
	hr = pAssembly->GetType_2(bstr_t("ManagedPluginLoader.ManagedPluginLoader"), &pManagedPluginLoaderType);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAssembly->GetType_2(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	VARIANT managedPluginLoaderInstance;
	VariantClear(&managedPluginLoaderInstance);
	hr = pAssembly->CreateInstance(bstr_t("ManagedPluginLoader.ManagedPluginLoader"), &managedPluginLoaderInstance);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAssembly->CreateInstance(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	/********* LoadManagedPlugins **********/

	_MethodInfoPtr pLoadManagedPluginsMethodInfo;
	hr = pManagedPluginLoaderType->GetMethod_6(bstr_t("LoadManagedPlugins"), &pLoadManagedPluginsMethodInfo);
	if (FAILED(hr) || !pLoadManagedPluginsMethodInfo)
	{
		MessageBox(NULL, L"[!] pManagedPluginLoaderType->GetMethod_6(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	SAFEARRAY *psaLoadManagedPlugins = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	VARIANT retVal;
	VariantClear(&retVal);
	hr = pLoadManagedPluginsMethodInfo->Invoke_3(managedPluginLoaderInstance, psaLoadManagedPlugins, &retVal);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pLoadManagedPluginsMethodInfo->Invoke_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	/********* FillApiFunction **********/

	_MethodInfoPtr pFillApiFunctionMethodInfo;
	hr = pManagedPluginLoaderType->GetMethod_6(bstr_t("FillApiFunction"), &pFillApiFunctionMethodInfo);
	if (FAILED(hr) || !pFillApiFunctionMethodInfo)
	{
		MessageBox(NULL, L"[!] pManagedPluginLoaderType->GetMethod_6(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	SAFEARRAY *psaFillApiFunction = SafeArrayCreateVector(VT_VARIANT, 0, 2);

	VARIANT fillApiArg1;
	VARIANT fillApiArg2;

	for (int i = 0;;i++)
	{
		if (function_records[i].functionName == NULL || function_records[i].functionAddress == NULL)
		{
			break;
		}

		VariantInit(&fillApiArg1);
		VariantInit(&fillApiArg2);

		InitVariantFromString(function_records[i].functionName, &fillApiArg1);
		InitVariantFromInt32((LONG)function_records[i].functionAddress, &fillApiArg2);

		LONG index = 0;
		SafeArrayPutElement(psaFillApiFunction, &index, &fillApiArg1);
		index = 1;
		SafeArrayPutElement(psaFillApiFunction, &index, &fillApiArg2);

		VariantClear(&retVal);
		hr = pFillApiFunctionMethodInfo->Invoke_3(managedPluginLoaderInstance, psaFillApiFunction, &retVal);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"[!] pLoadManagedPluginsMethodInfo->Invoke_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
			return -1;
		}
	}

	/************ GetPluginsMenus ***********/

	_MethodInfoPtr pGetPluginsMenusMethodInfo;
	hr = pManagedPluginLoaderType->GetMethod_6(bstr_t("GetPluginsMenus"), &pGetPluginsMenusMethodInfo);
	if (FAILED(hr) || !pGetPluginsMenusMethodInfo)
	{
		MessageBox(NULL, L"[!] pManagedPluginLoaderType->GetMethod_6(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	SAFEARRAY *psaGetPluginsMenus = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	VariantClear(&retVal);
	hr = pGetPluginsMenusMethodInfo->Invoke_3(managedPluginLoaderInstance, psaGetPluginsMenus, &retVal);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pLoadManagedPluginsMethodInfo->Invoke_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	managed_plugins_menu = (t_menu*)retVal.intVal;
	return 0;
};

extc t_menu * __cdecl ODBG2_Pluginmenu(wchar_t *type) {
	if (wcscmp(type, PWM_MAIN) == 0)
		return managed_plugins_menu;
	return NULL;
};