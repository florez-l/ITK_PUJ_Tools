// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

static const unsigned int Dim = 3;
using TPixel = short;

using TImage = ::itk::Image< TPixel, Dim >;
using TReader = ::itk::ImageFileReader< TImage >;
using TWriter = ::itk::ImageFileWriter< TImage >;


int main( int argc, char** argv )
{
  if( argc < 3 )
  {
    std::cerr
      << "Usage: " << argv[ 0 ] << " inputfile outputfile" << std::endl;
    return( EXIT_FAILURE );
  } // end if

  TReader::Pointer reader = TReader::New( );
  reader->SetFileName( argv[ 1 ] );

  TWriter::Pointer writer = TWriter::New( );
  writer->SetFileName( argv[ 2 ] );
  writer->SetInput( reader->GetOutput( ) );
  writer->UseCompressionOn( );

  try
  {
    writer->Update( );
  }
  catch( std::exception& err )
  {
    std::cerr << "Error caught: " << err.what( ) << std::endl;
    return( EXIT_FAILURE );
  } // end try
  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
