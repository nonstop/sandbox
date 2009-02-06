#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include <bfd.h>
#include "getopt.h"
#include <libiberty.h>

#define TST fprintf(stderr, "%s:%d %s\n", __FILE__, __LINE__, __FUNCTION__)

extern char *program_version;

static int base_names; /* -s, strip directory names.  */

static int naddr;  /* Number of addresses to process.  */
static char **addr;  /* Hex addresses to process.  */

static asymbol **syms;  /* Symbol table.  */

static struct option long_options[] = {
    {"basenames", no_argument, NULL, 's'},
    {"demangle", no_argument, NULL, 'C'},
    {"exe", required_argument, NULL, 'e'},
    {"functions", no_argument, NULL, 'f'},
    {"target", required_argument, NULL, 'b'},
    {"help", no_argument, NULL, 'H'},
    {"version", no_argument, NULL, 'V'},
    {0, no_argument, 0, 0}
};

static void usage PARAMS((FILE *, int));
static void slurp_symtab PARAMS((bfd *));
static void find_address_in_section PARAMS((bfd *, asection *, PTR));
static void translate_addresses PARAMS((bfd *));
static void process_file PARAMS((const char *, const char *));

/* Print a usage message to STREAM and exit with STATUS.  */

static void usage(FILE* stream, int status)
{
    if (status)
        fprintf(stream, "exit with status %d\n", status);
    exit(status);
}

/* Read in the symbol table.  */

static void slurp_symtab(bfd* abfd)
{
    long storage;
    long symcount;

    if ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0)
        return;

    storage = bfd_get_symtab_upper_bound(abfd);
    if (storage < 0)
        return;
//    bfd_fatal (bfd_get_filename (abfd));

    syms = (asymbol **) xmalloc(storage);

    symcount = bfd_canonicalize_symtab(abfd, syms);
    if (symcount < 0)
        return;
///    bfd_fatal (bfd_get_filename (abfd));
}

/* These global variables are used to pass information between
translate_addresses and find_address_in_section.  */

static bfd_vma pc;
static const char *filename;
static const char *functionname;
static unsigned int line;
static int found;

/* Look for an address in a section.  This is called via
bfd_map_over_sections.  */

static void find_address_in_section(bfd* abfd, asection* section, PTR data)
{
    bfd_vma vma;

    if (found)
        return;

    if ((bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0)
        return;

    vma = bfd_get_section_vma(abfd, section);
    if (pc < vma)
        return;

    found = bfd_find_nearest_line(abfd, section, syms, pc - vma,
                                  &filename, &functionname, &line);
}

/* Read hexadecimal addresses from stdin, translate into
file_name:line_number and optionally function name.  */

static void translate_addresses(bfd* abfd)
{
    int read_stdin = (naddr == 0);

    for (;;) {
        if (read_stdin) {
            char addr_hex[100];

            if (fgets(addr_hex, sizeof addr_hex, stdin) == NULL)
                break;
            pc = bfd_scan_vma(addr_hex, NULL, 16);
        } else {
            if (naddr <= 0)
                break;
            --naddr;
            pc = bfd_scan_vma(*addr++, NULL, 16);
        }

        found = 0;
        bfd_map_over_sections(abfd, find_address_in_section, (PTR) NULL);

        if (! found) {
            printf("??:0n");
        } else {

            if (base_names) {
                char *h;

                h = strrchr(filename, '/');
                if (h != NULL)
                    filename = h + 1;
            }

            printf("%s:%u\n", filename, line);
        }

        /* fflush() is essential for using this command as a server
        child process that reads addresses from a pipe and responds
        with line number information, processing one address at a
        time.  */
        fflush(stdout);
    }
}

/* Process a file.  */

static void process_file(const char* filename, const char* target)
{
    bfd *abfd;
    char **matching;

    abfd = bfd_openr(filename, target);
    if (abfd == NULL) {
        TST;
        return;
    }
//    bfd_fatal (filename);

    if (bfd_check_format(abfd, bfd_archive))
        return;
//    fatal ("%s: can not get addresses from archive", filename);

    if (! bfd_check_format_matches(abfd, bfd_object, &matching)) {
//bfd_nonfatal (bfd_get_filename (abfd));
        if (bfd_get_error() == bfd_error_file_ambiguously_recognized) {
//list_matching_formats (matching);
            free(matching);
        }
        xexit(1);
    }

    slurp_symtab(abfd);

    translate_addresses(abfd);

    if (syms != NULL) {
        free(syms);
        syms = NULL;
    }

    bfd_close(abfd);
}

int main(int argc, char* argv[])
{
    char *filename;
    char *target;
    int c;

    bfd_init();

    filename = NULL;
    target = NULL;
    while ((c = getopt_long(argc, argv, "b:Ce:sfHV", long_options, (int *) 0))
            != EOF) {
        switch (c) {
        case 0:
            break;  /* we've been given a long option */
        case 'b':
            target = optarg;
            break;
        case 'e':
            filename = optarg;
            break;
        case 's':
            base_names = 1;
            break;
        case 'V':
//   print_version ("addr2line");
            break;
        case 'H':
            usage(stdout, 0);
            break;
        default:
            usage(stderr, 1);
            break;
        }
    }

    if (filename == NULL)
        filename = "a.out";

    addr = argv + optind;
    naddr = argc - optind;

    TST;
    process_file(filename, target);
    TST;
    return 0;
}
