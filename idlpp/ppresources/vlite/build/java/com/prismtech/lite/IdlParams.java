package com.prismtech.lite;

import com.prismtech.lite.compilers.IdlcCmdOptions;

public class IdlParams
{
  public IdlParams (IdlcCmdOptions opts)
  {
    timestamp = !opts.nostamp;
    quiet = opts.quiet;
    lax = opts.lax;
    mapwide = opts.mapwide;
    mapld = opts.mapld;
    forcpp = opts.forcpp;
    dllname = opts.dllname;
    dllfile = opts.dllfile;
    xmlgen = !opts.noxml;
    allstructs = opts.allstructs;
    notopics = opts.notopics;
  }

  public boolean timestamp;
  public boolean quiet;
  public boolean lax;
  public boolean mapwide;
  public boolean mapld;
  public boolean forcpp;
  public boolean xmlgen;
  public boolean allstructs;
  public boolean notopics;
  public String dllname;
  public String dllfile;
  public String basename = null;
  public SymbolTable symtab = null;
  public LineTable linetab = null;
}

