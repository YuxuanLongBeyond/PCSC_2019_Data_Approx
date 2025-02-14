/**
* A C++ interface to gnuplot.
*
* @brief This is a direct translation from the C interface
* written by N. Devillard (which is available from
* http://ndevilla.free.fr/gnuplot/). As in the C interface
* this uses pipes and so wont run on a system that doesn't
* have POSIX pipe support.
*
* @authors Rajarshi Guha
*
* Improvements and optimizations have been added by:
* @authors David Cleres & Nicolas Lesimple
*
* Further improvements and details have been added by:
* @authors Yiting Zhang & Yuxuan Long
*
* @date 06/12/2019
*
* \file gnuplot_i.cpp
*
*/

#include "gnuplot_i.hpp"
#define PATH_MAXNAMESZ       4096

using namespace std;

template <typename Container>
void
stringtok (Container &container, string const &in,
           const char * const delimiters = " \t\n")
{
    const string::size_type len = in.length();
          string::size_type i = 0;

    while ( i < len )
    {
        // eat leading whitespace
        i = in.find_first_not_of (delimiters, i);
        if (i == string::npos)
            return;   // nothing left but white space

        // find the end of the token
        string::size_type j = in.find_first_of (delimiters, i);

        // push token
        if (j == string::npos) {
            container.push_back (in.substr(i));
            return;
        } else
            container.push_back (in.substr(i, j-i));

        // set up for next loop
        i = j + 1;
    }
}

//
// Constructors
//
Gnuplot::Gnuplot()
{
    if (getenv("DISPLAY") == nullptr)
      {
        this->valid = false;
        throw GnuplotException("cannot find DISPLAY variable");
      }
    if (!Gnuplot::get_program_path("gnuplot"))
      {
        this->valid = false;
        throw GnuplotException("Can't find gnuplot in your PATH");
      }
    
    this->gnucmd = popen("gnuplot","w");
    if (!this->gnucmd)
      {
        this->valid = false;
        throw GnuplotException("Could'nt open connection to gnuplot");
      }

    this->set_style("points");
    this->nplots = 0;
    this->valid = true;
}

Gnuplot::Gnuplot(const string &style)
{
    if (getenv("DISPLAY") == nullptr)
      {
        this->valid = false;
        throw GnuplotException("cannot find DISPLAY variable");
      }
    if (!Gnuplot::get_program_path("gnuplot"))
      {
        this->valid = false;
        throw GnuplotException("Can't find gnuplot in your PATH");
      }

    this->gnucmd = popen("gnuplot","w");
    if (!this->gnucmd)
      {
        this->valid = false;
        throw GnuplotException("Could'nt open connection to gnuplot");
      }
    this->set_style(style);
    this->nplots = 0;
    this->valid = true;
}

Gnuplot::Gnuplot(
         const string &title,
         const string &style,
         const string &labelx,  const string &labely,
         vector<double> const& x, vector<double> const& y)
{
    if (getenv("DISPLAY") == nullptr)
      {
        this->valid = false;
        throw GnuplotException("cannot find DISPLAY variable");
      }
    if (!Gnuplot::get_program_path("gnuplot"))
      {
        this->valid = false;
        throw GnuplotException("Can't find gnuplot in your PATH");
      }


    this->gnucmd = popen("gnuplot","w");
    if (!this->gnucmd)
      {
        this->valid = false;
        throw GnuplotException("Could'nt open connection to gnuplot");
      }
    this->nplots = 0;
    this->valid = true;


    if (x.empty() || y.empty())
        throw GnuplotException("vectors too small");

    if (style.empty())
        this->set_style("lines");
    else
        this->set_style(style);

    if (labelx.empty())
        this->set_xlabel("X");
    else
        this->set_xlabel(labelx);
    if (labely.empty())
        this->set_ylabel("Y");
    else
        this->set_ylabel(labely);
    
    this->plot_xy(x,y,title);

    cout << "Press enter to continue" << endl;
    while (getchar() != '\n'){}
}

Gnuplot::Gnuplot(
        const string &title,
        const string &titlem,
        const string &style,
        const string &labelx,  const string &labely,
        vector<double> const& x, vector<double> const& y, vector<double> const& xm, vector<double> const& ym)
{
    if (getenv("DISPLAY") == nullptr)
    {
        this->valid = false;
        throw GnuplotException("cannot find DISPLAY variable");
    }
    if (!Gnuplot::get_program_path("gnuplot"))
    {
        this->valid = false;
        throw GnuplotException("Can't find gnuplot in your PATH");
    }


    this->gnucmd = popen("gnuplot","w");
    if (!this->gnucmd)
    {
        this->valid = false;
        throw GnuplotException("Could'nt open connection to gnuplot");
    }
    this->nplots = 0;
    this->valid = true;


    if (x.empty() || y.empty() || xm.empty() || ym.empty())
        throw GnuplotException("vectors too small");

    if (style.empty())
        this->set_style("lines");
    else
        this->set_style(style);

    if (labelx.empty())
        this->set_xlabel("X");
    else
        this->set_xlabel(labelx);
    if (labely.empty())
        this->set_ylabel("Y");
    else
        this->set_ylabel(labely);

    this->plot_xy(x,y,title);
    this->plot_xy(xm,ym,titlem);

    cout << "Press enter to continue" << endl;
    while (getchar() != '\n'){}
}

Gnuplot::Gnuplot(
         const string &title,
         const string &style,
         const string &labelx,  const string &labely,
         vector<double> const& x)
{
    if (getenv("DISPLAY") == nullptr)
      {
        this->valid = false;
        throw GnuplotException("cannot find DISPLAY variable");
      }
    if (!this->get_program_path("gnuplot"))
      {
        this->valid = false;
        throw GnuplotException("Can't find gnuplot in your PATH");
      }


    this->gnucmd = popen("gnuplot","w");
    if (!this->gnucmd)
      {
        this->valid = false;
        throw GnuplotException("Could'nt open connection to gnuplot");
      }
    this->nplots = 0;
    this->valid = true;
    
    this->nplots = 0;
    this->valid = true;


    if (x.empty())
        throw GnuplotException("vector too small");
    if (!this->gnucmd)
        throw GnuplotException("Could'nt open connection to gnuplot");

    if (style.empty())
        this->set_style("lines");
    else
        this->set_style(style);

    if (labelx.empty())
        this->set_xlabel("X");
    else
        this->set_xlabel(labelx);
    if (labely.empty())
        this->set_ylabel("Y");
    else
        this->set_ylabel(labely);
    
    this->plot_x(x,title);

    cout << "Press enter to continue" << endl;
    while (getchar() != '\n'){}
}

//
// Destructor
// 
Gnuplot::~Gnuplot()
{
    if (!(this->to_delete).empty())
      {
        for (size_t i(0); i < this->to_delete.size(); i++)
            remove(this->to_delete[i].c_str());
        to_delete.clear();
      }
    if (pclose(this->gnucmd) == -1)
        cerr << "Problem closing communication to gnuplot" << endl;
}

bool Gnuplot::is_valid()
{
    return(this->valid);
}

bool Gnuplot::get_program_path(const string& pname)
{
    list<string> ls;
    char *path;

    path = getenv("PATH");
    if (!path)
      {
        cerr << "Path is not set" << endl;
        return false;
      }
    else
      {
        stringtok(ls,path,":");
        for (list<string>::const_iterator i = ls.begin();
                i != ls.end(); ++i)
          {
            string tmp = (*i) + "/" + pname;
            if (access(tmp.c_str(),X_OK) == 0)
                return true;
          }
      }
    return false;
}

void Gnuplot::reset_plot()
{       
    if (!this->to_delete.empty())
      {
        for (auto & i : this->to_delete)
            remove(i.c_str());
        to_delete.clear();
      }
    this->nplots = 0;
}

void Gnuplot::set_style(const string &stylestr)
{
    if (stylestr != "lines" &&
            stylestr != "points" &&
            stylestr != "linespoints" &&
            stylestr != "impulses" &&
            stylestr != "dots" &&
            stylestr != "steps" &&
            stylestr != "errorbars" &&
            stylestr != "boxes" &&
            stylestr != "boxerrorbars")
        this->pstyle = string("points");
    else
        this->pstyle = stylestr;
}

void Gnuplot::cmd(const char *cmdstr, ...)
{
    va_list ap;
    char local_cmd[GP_CMD_SIZE];

    va_start(ap, cmdstr);
    vsprintf(local_cmd, cmdstr, ap);
    va_end(ap);
    strcat(local_cmd,"\n");
    fputs(local_cmd,this->gnucmd);
    fflush(this->gnucmd);
}

void Gnuplot::set_ylabel(const string &label)
{
    ostringstream cmdstr;

    cmdstr << "set xlabel \"" << label << "\"";
    this->cmd(cmdstr.str().c_str());
}

void Gnuplot::set_xlabel(const string &label)
{
    ostringstream cmdstr;

    cmdstr << "set xlabel \"" << label << "\"";
    this->cmd(cmdstr.str().c_str());
}

// 
// Plots a linear equation (where you supply the
// slope and intercept)
//
void Gnuplot::plot_slope(double a, double b, const string &title)
{
    ostringstream stitle;
    ostringstream cmdstr;

    if (title.empty())
        stitle << "no title";
    else
        stitle << title;

    if (this->nplots > 0)
        cmdstr << "replot " << a << " * x + " << b << " title \"" << stitle.str() << "\" with " << pstyle;
    else
        cmdstr << "plot " << a << " * x + " << b << " title \"" << stitle.str() << "\" with " << pstyle;
    this->cmd(cmdstr.str().c_str());
    this->nplots++;
}

//
// Plot an equation which is supplied as a string
// 
void Gnuplot::plot_equation(const string &equation, const string &title)
{
    string titlestr, plotstr;
    ostringstream cmdstr;

    if (title.empty())
        titlestr = "no title";
    else
        titlestr = title;

    if (this->nplots > 0)
        plotstr = "replot";
    else
        plotstr = "plot";

    cmdstr << plotstr << " " << equation << " " << "title \"" << titlestr << "\" with " << this->pstyle;
    this->cmd(cmdstr.str().c_str());
    this->nplots++;
}

void Gnuplot::plot_x(vector<double> d, const string &title)
{
    ofstream tmp;
    ostringstream cmdstr;
    char name[] = "/tmp/gnuplotiXXXXXX";

    if (this->to_delete.size() == GP_MAX_TMP_FILES - 1)
      {
        cerr << "Maximum number of temporary files reached (" << GP_MAX_TMP_FILES << "): cannot open more files" << endl;
        return;
      }

    //
    //open temporary files for output
    if (mkstemp(name) == -1)
      {
        cerr << "Cannot create temporary file: exiting plot" << endl;
        return;
      }
    tmp.open(name);
    if (tmp.bad())
      {
        cerr << "Cannot create temorary file: exiting plot" << endl;
        return;
      }

    //
    // Save the temporary filename
    // 
    this->to_delete.emplace_back(name);

    //
    // write the data to file
    //
    for (double i : d)
        tmp << i << endl;
    tmp.flush();    
    tmp.close();

    //
    // command to be sent to gnuplot
    //
    if (this->nplots > 0)
        cmdstr << "replot ";
    else cmdstr << "plot ";
    if (title.empty())
        cmdstr << "\"" << name << "\" with " << this->pstyle;
    else
        cmdstr << "\"" << name << "\" title \"" << title << "\" with " << this->pstyle;

    //
    // Do the actual plot
    //
    this->cmd(cmdstr.str().c_str());
    this->nplots++;
}
    
void Gnuplot::plot_xy(vector<double> x, vector<double> y, const string &title)
{
    ofstream tmp;
    ostringstream cmdstr;
    char name[] = "/tmp/gnuplotiXXXXXX";
    
    // should raise an exception
    if (x.size() != x.size())
        return;

    if ((this->to_delete).size() == GP_MAX_TMP_FILES - 1)
      {
        cerr << "Maximum number of temporary files reached (" << GP_MAX_TMP_FILES << "): cannot open more files" << endl;
        return;
      }

    //
    //open temporary files for output
    //
    if (mkstemp(name) == -1)
      {
        cerr << "Cannot create temporary file: exiting plot" << endl;
        return;
      }
    tmp.open(name);
    if (tmp.bad())
      {
        cerr << "Cannot create temorary file: exiting plot" << endl;
        return;
      }

    //
    // Save the temporary filename
    // 
    this->to_delete.emplace_back(name);

    //
    // write the data to file
    //
    for (int i = 0; i < x.size(); i++)
        tmp << x[i] << " " << y[i] << endl;
    tmp.flush();    
    tmp.close();

    //
    // command to be sent to gnuplot
    //
    if (this->nplots > 0)
        cmdstr << "replot ";
    else cmdstr << "plot ";
    if (title.empty())
        cmdstr << "\"" << name << "\" with " << this->pstyle;
    else
        cmdstr << "\"" << name << "\" title \"" << title << "\" with " << this->pstyle;

    //
    // Do the actual plot
    //
    this->cmd(cmdstr.str().c_str());
    this->nplots++;
}


