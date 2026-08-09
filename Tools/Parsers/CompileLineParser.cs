using System;

public class CompileLineParser
{
  public string SourceLine;
  public bool Error;
  public string Type = "EXE";
  public Dictionary<string,string>Functions;

  public CompileLineParser(string Line)
  {
    this.SourceLine = Line;
    this.Functions = new Dictionary<string,string>{};
    this.Parse();
  }

  public void Parse()
  {
    string Code = "";
    if (this.IsVaild())
    {
      Code = this.GetCode();
    }
    else
    {
      Error = true;
    }

    string[] sections = this.GetSections(Code);
    if (!this.VaildSections(sections))
    {
      this.Error = true;
      return;
    }
    this.ParseSections(sections);
  }
  public bool ParseSections(string[] sections)
  {
    foreach (string s in sections)
    {
       this.ParseSection(s);
    }
    return true;
  }

  public bool ParseSection(string section)
  {
     string t_s = section.Trim();
     bool SectionType = false;

     if (t_s[0] == '|')
     {
       SectionType = true;
     }
     if (SectionType)
     {
       t_s.Replace("|","");
     }

     return true;
  }

  public string GetName(string section)
  {
    string Name = "";
    foreach (char i in section.ToCharArray())
    {
      if (i == '(')
      {
        break;
      }
      Name += i;
    }
    return Name;
  }

  public bool VaildSections(string[] sections)
  {
    foreach (string i in sections)
    {
      if (!this.VaildSection(i))
      {
        return false;
      }
    }
    return true;
  }

  public bool VaildSection(string section)
  {
    string fn = "";
    for (int i = 0 ; section[i] != "(" ; i++)
    {
      fn += section[i];
    }

    if (!this.NameVaild(fn))
    {
      return false;
    }
    return true;
  }

  public bool IsVaild()
  {
    bool check_s = false;
    foreach (char i in this.SourceLine.ToCharArray())
    {
       if (i == '*')
       {
         if (check_s) return true;
         check_s = true;
       }
    }
    return true;
  }

  public string GetCode()
  {
    bool Get = false;
    string r = "";

    foreach (char i in this.SourceLine.ToCharArray())
    {
      if (i == '*')
      {
        if (Get)
        {
          Get = false;
        }
        Get = true;
        continue;
      }

      if (Get)
      {
        r += i;
      }
    }
    return r;
  }

  public string[] GetSections(string Code)
  {
    return Code.Split(",");
  }

  public bool NameVaild(string Name)
  {
    if (!char.IsLetter(Name[0]))
    {
      return false;
    }
    foreach (char i in Name)
    {
      if (!char.IsLetter(i) && !char.IsNumber(i))
      {
        return false;
      }
    }
    return true;
  }
}
