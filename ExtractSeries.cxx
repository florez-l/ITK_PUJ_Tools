// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>

#include <itkGDCMSeriesFileNames.h>
#include <itkImage.h>
#include <itkImageSeriesReader.h>
#include <itkImageFileWriter.h>

static const unsigned int Dim = 3;
using TPixel = short;

using TImage = ::itk::Image< TPixel, Dim >;
using TReader = ::itk::ImageSeriesReader< TImage >;
using TWriter = ::itk::ImageFileWriter< TImage >;

int main( int argc, char** argv )
{
  if( argc < 2 )
  {
    std::cerr
      << "Usage: " << argv[ 0 ] << " path" << std::endl;
    return( EXIT_FAILURE );
  } // end if

  // Read path data
  ::itk::GDCMSeriesFileNames::Pointer f = ::itk::GDCMSeriesFileNames::New( );
  f->LoadPrivateTagsOn( );
  f->LoadSequencesOn( );
  f->RecursiveOn( );
  f->SetDirectory( argv[ 1 ] );
  f->SetInputDirectory( argv[ 1 ] );
  f->SetUseSeriesDetails( true );

  // Process each serie
  const std::vector< std::string >& ids = f->GetSeriesUIDs( );
  unsigned long i = 1;
  for( const std::string& id: ids )
  {
    // Get filenames
    std::vector< std::string > fnames = f->GetFileNames( id );

    // Read serie
    TReader::Pointer reader = TReader::New( );
    for( const std::string& fname: fnames )
      reader->AddFileName( fname );

    std::stringstream out_fname;
    out_fname << id << ".mha";

    TWriter::Pointer writer = TWriter::New( );
    writer->SetFileName( out_fname.str( ) );
    writer->SetInput( reader->GetOutput( ) );
    writer->UseCompressionOn( );
    std::cout
      << "Saving \"" << writer->GetFileName( )
      << "\" (" << i++ << "/" << ids.size( ) << ")... ";
    std::cout.flush( );
    try
    {
      writer->Update( );
    }
    catch( std::exception& err )
    {
      std::cerr << " *** Error caught: " << err.what( ) << std::endl;
    } // end try
    std::cout << "done!" << std::endl;
  } // end for
  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
